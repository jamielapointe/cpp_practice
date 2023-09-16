#include <gtest/gtest.h>

#include "cpp_practice/length_of_longest_substring.h"

using cpp_practice::cpp_20::length_of_longest_substring::
    length_of_longest_substring;

TEST(LengthOfLongestSubstringTest, Basic00) {
  EXPECT_EQ(length_of_longest_substring("abcabcbb"), 3);
}

TEST(LengthOfLongestSubstringTest, Basic01) {
  EXPECT_EQ(length_of_longest_substring("bbbbb"), 1);
}

TEST(LengthOfLongestSubstringTest, Basic02) {
  EXPECT_EQ(length_of_longest_substring("pwwkew"), 3);
}
