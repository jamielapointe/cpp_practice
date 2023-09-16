
#include <gtest/gtest.h>

#include "cpp_practice/bit_manipulations/list_sum_with_mask.h"

using cpp_practice::bit_manipulations::list_sum_with_mask::ListNode;

// NOLINTBEGIN(cppcoreguidelines-owning-memory,
// cppcoreguidelines-avoid-magic-numbers)

/*
Input:
  3 -> 1 -> 5 represents the integer 315
  5 -> 9 -> 2 represents the integer 592
  (3 -> 1 -> 5) + (5 -> 9 -> 2)
  mask = 0b_0000_0101
Output:
  8 -> 0 -> 7
*/
TEST(ListSumWithMaskTest, Test00) {
  auto l1 = std::make_unique<ListNode>(3);
  l1->next = std::make_unique<ListNode>(1);
  l1->next->next = std::make_unique<ListNode>(5);
  auto l2 = std::make_unique<ListNode>(5);
  l2->next = std::make_unique<ListNode>(9);
  l2->next->next = std::make_unique<ListNode>(2);
  auto expected = std::make_unique<ListNode>(8);
  expected->next = std::make_unique<ListNode>(0);
  expected->next->next = std::make_unique<ListNode>(7);
  auto result = list_sum_with_mask(l1, l2, 0b00000101);
  auto expected_current = expected.get();
  auto result_current = result.get();
  while (result_current != nullptr && expected_current != nullptr) {
    EXPECT_EQ(result_current->val, expected_current->val);
    result_current = result_current->next.get();
    expected_current = expected_current->next.get();
  }
  EXPECT_EQ(result_current, nullptr);
  EXPECT_EQ(expected_current, nullptr);
}

/*
Input:
       8 -> 5 -> 7 represents the integer   857
  9 -> 8 -> 7 -> 6 represents the integer 9_876
  mask = 0b_0000_1101
  (8 -> 5 -> 7) + (9 -> 8 -> 7 -> 6)
Output:
  1 -> 0 -> 6 -> 1 -> 3 represents the integer 10_613
*/
TEST(ListSumWithMaskTest, Test01) {
  auto l1 = std::make_unique<ListNode>(8);
  l1->next = std::make_unique<ListNode>(5);
  l1->next->next = std::make_unique<ListNode>(7);
  auto l2 = std::make_unique<ListNode>(9);
  l2->next = std::make_unique<ListNode>(8);
  l2->next->next = std::make_unique<ListNode>(7);
  l2->next->next->next = std::make_unique<ListNode>(6);
  auto expected = std::make_unique<ListNode>(1);
  expected->next = std::make_unique<ListNode>(0);
  expected->next->next = std::make_unique<ListNode>(6);
  expected->next->next->next = std::make_unique<ListNode>(1);
  expected->next->next->next->next = std::make_unique<ListNode>(3);
  auto result = list_sum_with_mask(l1, l2, 0b00001101);
  auto expected_current = expected.get();
  auto result_current = result.get();
  while (result_current != nullptr && expected_current != nullptr) {
    EXPECT_EQ(result_current->val, expected_current->val);
    result_current = result_current->next.get();
    expected_current = expected_current->next.get();
  }
  EXPECT_EQ(result_current, nullptr);
  EXPECT_EQ(expected_current, nullptr);
}

/*
Input:
       8 -> 5 -> 7 represents the integer   857
  9 -> 9 -> 9 -> 9 represents the integer 9_999
  mask = 0b_0000_0000
  (8 -> 5 -> 7) + (9 -> 9 -> 9 -> 9)
Output:
 0 -> 0 -> 0 -> 0 represents the integer 0
*/
TEST(ListSumWithMaskTest, Test02) {
  auto l1 = std::make_unique<ListNode>(8);
  l1->next = std::make_unique<ListNode>(5);
  l1->next->next = std::make_unique<ListNode>(7);
  auto l2 = std::make_unique<ListNode>(9);
  l2->next = std::make_unique<ListNode>(9);
  l2->next->next = std::make_unique<ListNode>(9);
  l2->next->next->next = std::make_unique<ListNode>(9);
  auto expected = std::make_unique<ListNode>(0);
  expected->next = std::make_unique<ListNode>(0);
  expected->next->next = std::make_unique<ListNode>(0);
  expected->next->next->next = std::make_unique<ListNode>(0);
  auto result = list_sum_with_mask(l1, l2, 0b00000000);
  auto expected_current = expected.get();
  auto result_current = result.get();
  while (result_current != nullptr && expected_current != nullptr) {
    EXPECT_EQ(result_current->val, expected_current->val);
    result_current = result_current->next.get();
    expected_current = expected_current->next.get();
  }
  EXPECT_EQ(result_current, nullptr);
  EXPECT_EQ(expected_current, nullptr);
}

TEST(ListSumWithMaskTest, NullResult) {
  std::unique_ptr<ListNode> l1 = nullptr;
  std::unique_ptr<ListNode> l2 = nullptr;
  auto result = list_sum_with_mask(l1, l2, 0b00000000);
  EXPECT_EQ(result, nullptr);
}

// NOLINTEND(cppcoreguidelines-owning-memory,
// cppcoreguidelines-avoid-magic-numbers)
