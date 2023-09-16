
#include <gtest/gtest.h>

#include "cpp_practice/min_window.h"

using cpp_practice::cpp_20::min_window::min_window;
using std::string_view;

TEST(MinWindowTest, Basic00) {
  EXPECT_EQ(min_window("ADOBECODEBANC", "ABC"), "BANC");
}

TEST(MinWindowTest, Basic01) { EXPECT_EQ(min_window("a", "a"), "a"); }

TEST(MinWindowTest, Basic02) { EXPECT_EQ(min_window("a", "aa"), ""); }

TEST(MinWindowTest, Basic03) { EXPECT_EQ(min_window("aa", "aa"), "aa"); }

TEST(MinWindowTest, Basic04) { EXPECT_EQ(min_window("bbaa", "aba"), "baa"); }

TEST(MinWindowTest, Basic06) { EXPECT_EQ(min_window("bbaa", "abaaa"), ""); }

TEST(MinWindowTest, LongTest00) {
  EXPECT_EQ(min_window("aaaaaaaaaaaabbbbbcdd", "abcdd"), "abbbbbcdd");
}

TEST(MinWindowTest, NotFound) {
  EXPECT_EQ(min_window("aaaaaaaaaaaabbbbbcdd", "abcde"), "");
}