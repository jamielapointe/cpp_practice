/*
 You are given two linked lists representing two non-negative numbers.
 The digits are stored in left to right order of the integer the represent.
 You are also givin a circular mask. The mask is a 8-bit integer.  The mask
 is circular such that the 0th bit in the mask correspond the 0th digit of the
 integer in the linked list, the 8th digit (if available) in the integer, the
16th digit (if available), and so on.  If the masked bit is a 1 then sum the
digits, otherwise add 0 to the resultant linked list for that digit.

Write a function that adds the two numbers and returns the sum as a linked list.

For example:
Input:
  3 -> 1 -> 5 represents the integer 315
  (3 -> 1 -> 5) + (5 -> 9 -> 2)
  mask = 0b_0000_0101
Output:
  8 -> 0 -> 7
*/

#include <cstdint>

namespace cpp_practice::bit_manipulations::list_sum_with_mask {

static constexpr int kBase10 = 10;
static constexpr uint8_t kMaskBitLength = 8;

// NOLINTBEGIN(cppcoreguidelines-owning-memory)

// Definition for singly-linked list.
struct ListNode {
  int val{0};
  ListNode* next{nullptr};
  explicit ListNode(int x) : val(x) {}
};

inline ListNode* list_sum_with_mask(ListNode* a, ListNode* b, uint8_t mask) {
  ListNode* result = nullptr;
  if (a == nullptr || b == nullptr) {
    return result;
  }

  // Reverse the lists
  auto a_current = a;
  ListNode* a_reverse = new ListNode(a_current->val);
  a_current = a_current->next;
  while (a_current != nullptr) {
    auto temp = a_reverse;
    a_reverse = new ListNode(a_current->val);
    a_reverse->next = temp;
    a_current = a_current->next;
  }

  auto b_current = b;
  ListNode* b_reverse = new ListNode(b_current->val);
  b_current = b_current->next;
  while (b_current != nullptr) {
    auto temp = b_reverse;
    b_reverse = new ListNode(b_current->val);
    b_reverse->next = temp;
    b_current = b_current->next;
  }

  // Start building result in reverse
  int carry = 0;
  auto a_reverse_current = a_reverse;
  auto b_reverse_current = b_reverse;
  uint8_t mask_shift{0x00};
  uint8_t mask_mask{0x01};
  ListNode* result_reverse = nullptr;
  ListNode* result_reverse_head = nullptr;
  while (a_reverse_current != nullptr || b_reverse_current != nullptr) {
    int sum = carry;
    uint8_t mask_bit = (mask & mask_mask) >> mask_shift;
    if (mask_bit == 1) {
      if (a_reverse_current != nullptr) {
        sum += a_reverse_current->val;
      }
      if (b_reverse_current != nullptr) {
        sum += b_reverse_current->val;
      }
      carry = sum / kBase10;
      sum = sum % kBase10;
    } else {
      carry = 0;
    }
    if (result_reverse == nullptr) {
      result_reverse = new ListNode(sum);
      result_reverse_head = result_reverse;
    } else {
      result_reverse->next = new ListNode(sum);
      result_reverse = result_reverse->next;
    }
    mask_shift = (mask_shift + 1) % kMaskBitLength;
    mask_mask = static_cast<uint8_t>(mask_shift << 1);
    if (a_reverse_current != nullptr) {
      a_reverse_current = a_reverse_current->next;
    }
    if (b_reverse_current != nullptr) {
      b_reverse_current = b_reverse_current->next;
    }
  }

  // put reverse in the proper order
  ListNode* result_reverse_current = result_reverse_head;
  while (result_reverse_current != nullptr) {
    auto temp = result_reverse_current->next;
    result_reverse_current->next = result;
    result = result_reverse_current;
    result_reverse_current = temp;
  }

  return result;
}

// NOLINTEND(cppcoreguidelines-owning-memory)

}  // namespace cpp_practice::bit_manipulations::list_sum_with_mask
