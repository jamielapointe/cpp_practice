///\file length_of_longest_substring.h
///\author Jamie LaPointe (jamie.lapointe@gmail.com)
///\brief LeetCode 3, Longest substring without repeating characters
///\version 0.1
///\date 2023-08-02
///\details Given a string s, find the length of the longest substring without
/// repeating characters.
///@copyright Copyright (c) 2023
///

#pragma once

#include <string>
#include <unordered_set>

namespace cpp_practice::cpp_20::length_of_longest_substring {

///\brief Find the length of the longest substring without repeating characters
///\details Given a string s, find the length of the longest substring without
/// repeating characters.
///\param s The string to search
///\return The length of the longest substring without repeating characters
int length_of_longest_substring(std::string s) {
  using std::max;
  using std::string;
  using std::unordered_set;

  unordered_set<char> seen_letters;
  int curr{0};
  int max_len{0};
  size_t right{0};
  size_t left{0};
  while (right < s.size()) {
    // expand to the right until reach the end of the string or we find a
    // duplicate letter
    while (right < s.size() &&
           seen_letters.find(s[right]) == seen_letters.end()) {
      seen_letters.insert(s[right]);
      ++curr;
      max_len = max(max_len, curr);
      ++right;
    }
    // no sense in doing anything else if right has popped off the end
    if (right == s.size()) {
      return max_len;
    }
    // We know there is a duplicate in the window. Push in from the left until
    // we find it and remove it
    bool do_exit = false;
    while (!do_exit) {
      // we found it, remove it, shift to the left and exit the loop
      if (s[left] == s[right]) {
        do_exit = true;
      }
      seen_letters.erase(s[left]);
      --curr;
      ++left;
    }
  }
  return max_len;
}
}  // namespace cpp_practice::cpp_20::length_of_longest_substring
