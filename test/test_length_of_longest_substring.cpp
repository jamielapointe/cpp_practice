#include <gtest/gtest.h>

#include "cpp_practice/length_of_longest_substring.h"

using cpp_practice::cpp_20::length_of_longest_substring::
    length_of_longest_substring;

TEST(LengthOfLongestSubstringTest, Basic00) {
  EXPECT_EQ(length_of_longest_substring("abcabcbb"), 3);
}
