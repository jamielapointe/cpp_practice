
#include <gtest/gtest.h>

#include "cpp_practice/reverse_words.h"

using cpp_practice::cpp_20::reverse_words::reverseWordsSlowRegex;
using cpp_practice::cpp_20::reverse_words::reverseWordsStringStream;

TEST(ReverseWordsTest, EmptyString) {
  EXPECT_EQ(reverseWordsSlowRegex(""), "");
  EXPECT_EQ(reverseWordsStringStream(""), "");
}

TEST(ReverseWordsTest, SingleWord) {
  EXPECT_EQ(reverseWordsSlowRegex("hello"), "hello");
  EXPECT_EQ(reverseWordsStringStream("hello"), "hello");
}

TEST(ReverseWordsTest, TwoWords) {
  EXPECT_EQ(reverseWordsSlowRegex("hello world"), "world hello");
  EXPECT_EQ(reverseWordsStringStream("hello world"), "world hello");
}

TEST(ReverseWordsTest, MultipleWords) {
  EXPECT_EQ(reverseWordsSlowRegex("the sky is blue"), "blue is sky the");
  EXPECT_EQ(reverseWordsStringStream("the sky is blue"), "blue is sky the");
}

TEST(ReverseWordsTest, MultipleWordsWithExtraSpaces) {
  EXPECT_EQ(reverseWordsSlowRegex("  hello world  "), "world hello");
  EXPECT_EQ(reverseWordsStringStream("  hello world  "), "world hello");
}

TEST(ReverseWordsTest, MultipleWordsWithExtraSpacesBetweenWords) {
  EXPECT_EQ(reverseWordsSlowRegex("a good   example"), "example good a");
  EXPECT_EQ(reverseWordsStringStream("a good   example"), "example good a");
}
