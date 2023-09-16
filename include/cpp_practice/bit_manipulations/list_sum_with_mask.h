/*
 You are given two linked lists representing two non-negative numbers.
 The digits are stored in left to right order of the integer they represent.
 You are also givin a circular mask. The mask is a 8-bit integer.  The mask
 is circular such that the 0th bit in the mask correspond the 0th digit of the
 integer in the linked list, the 8th digit (if available) in the integer, the
 16th digit (if available), and so on.  If the masked bit is a 1 then sum the
 digits, otherwise add 0 to the resultant linked list for that digit.

 Write a function that adds the two numbers and returns the sum as a linked
 list.

For example:
Input:
  3 -> 1 -> 5 represents the integer 315
  (3 -> 1 -> 5) + (5 -> 9 -> 2)
  mask = 0b_0000_0101
Output:
  8 -> 0 -> 7
*/

#include <cstdint>
#include <memory>

namespace cpp_practice::bit_manipulations::list_sum_with_mask {

static constexpr int kBase10 = 10;
static constexpr int kNumBitsUint32 = 32;
static constexpr int kMaxMaskShift = 7;
static constexpr int kMaxMask = 0b10000000;

// NOLINTBEGIN(cppcoreguidelines-owning-memory)

// Definition for singly-linked list.
template <typename T>
struct ListNod_T {
  T val{0};
  std::unique_ptr<ListNod_T> next{nullptr};
  explicit ListNod_T(T x) : val(x) {}
};

using ListNode = ListNod_T<int>;

inline std::unique_ptr<ListNode> list_sum_with_mask(
    std::unique_ptr<ListNode>& a, std::unique_ptr<ListNode>& b, uint32_t mask) {
  std::unique_ptr<ListNode> result = nullptr;
  if (a == nullptr || b == nullptr) {
    return result;
  }

  // Reverse the lists
  auto a_current = a.get();
  auto a_reverse = std::make_unique<ListNode>(a_current->val);
  a_current = a_current->next.get();
  while (a_current != nullptr) {
    auto temp = std::move(a_reverse);
    a_reverse = std::make_unique<ListNode>(a_current->val);
    a_reverse->next = std::move(temp);
    a_current = a_current->next.get();
  }

  auto b_current = b.get();
  auto b_reverse = std::make_unique<ListNode>(b_current->val);
  b_current = b_current->next.get();
  while (b_current != nullptr) {
    auto temp = std::move(b_reverse);
    b_reverse = std::make_unique<ListNode>(b_current->val);
    b_reverse->next = std::move(temp);
    b_current = b_current->next.get();
  }

  // Start building result in reverse
  int carry = 0;
  auto a_reverse_current = a_reverse.get();
  auto b_reverse_current = b_reverse.get();
  uint32_t mask_shift{0x00};
  uint32_t mask_mask{0x01};
  while (a_reverse_current != nullptr || b_reverse_current != nullptr) {
    int sum = carry;
    uint32_t mask_bit = (mask & mask_mask) >> mask_shift;
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
    if (result == nullptr) {
      result = std::make_unique<ListNode>(sum);
    } else {
      // reverse the result
      auto temp = std::move(result);
      result = std::make_unique<ListNode>(sum);
      result->next = std::move(temp);
    }
    mask_shift = mask_shift < kMaxMaskShift ? (mask_shift + 1) : 0;
    mask_mask = mask_mask < kMaxMask ? (mask_mask << 1) : 0b00000001;
    if (a_reverse_current != nullptr) {
      a_reverse_current = a_reverse_current->next.get();
    }
    if (b_reverse_current != nullptr) {
      b_reverse_current = b_reverse_current->next.get();
    }
  }

  if (carry > 0) {
    auto temp = std::move(result);
    result = std::make_unique<ListNode>(carry);
    result->next = std::move(temp);
  }

  return result;
}

// NOLINTEND(cppcoreguidelines-owning-memory)

}  // namespace cpp_practice::bit_manipulations::list_sum_with_mask
