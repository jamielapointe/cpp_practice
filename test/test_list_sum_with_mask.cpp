
#include <gtest/gtest.h>

#include "cpp_practice/bit_manipulations/list_sum_with_mask.h"

using cpp_practice::bit_manipulations::list_sum_with_mask::ListNode;

// NOLINTBEGIN(cppcoreguidelines-owning-memory,
// cppcoreguidelines-avoid-magic-numbers)
TEST(ListSumWithMaskTest, Test00) {
  auto l1 = new ListNode(3);
  l1->next = new ListNode(1);
  l1->next->next = new ListNode(5);
  auto l2 = new ListNode(5);
  l2->next = new ListNode(9);
  l2->next->next = new ListNode(2);
  auto expected = new ListNode(8);
  expected->next = new ListNode(0);
  expected->next->next = new ListNode(7);
  auto result = list_sum_with_mask(l1, l2, 0b00000101);
  auto expected_current = expected;
  auto result_current = result;
  while (result_current != nullptr && expected_current != nullptr) {
    EXPECT_EQ(result_current->val, expected_current->val);
    result_current = result_current->next;
    expected_current = expected_current->next;
  }
  EXPECT_EQ(result_current, nullptr);
  EXPECT_EQ(expected_current, nullptr);
}
// NOLINTEND(cppcoreguidelines-owning-memory,
// cppcoreguidelines-avoid-magic-numbers)
