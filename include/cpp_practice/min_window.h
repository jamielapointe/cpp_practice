///\file min_window.h
///\author Jamie LaPointe (jamie.lapointe@gmail.com)
///\brief LeetCode 76. Minimum Window Substring
///\version 0.1
///\date 2023-07-30
///\details Given two strings s and t of lengths m and n respectively, return
/// the minimum window substring of s such that every character in t (including
/// duplicates) is included in the window. If there is no such substring, return
/// the empty string "". The test cases will be generated such that the answer
/// is unique.
///@copyright Copyright (c) 2023
///

#pragma once

#include <algorithm>
#include <string>
#include <string_view>
#include <unordered_map>

namespace cpp_practice::cpp_20::min_window {

///\brief Find the minimum window substring
///
///\param s The string to search for the substring
///\param t The substring to search for
///\return std::string The minimum window substring
std::string min_window(std::string s, std::string t) {
  using std::sort;
  using std::string;
  using std::unordered_map;
  // if t is larger, than s then no valid window can exist so return empty
  // string
  if (t.size() > s.size()) {
    return "";
  }
  // capture number of occurrences for each unique character in t
  unordered_map<char, size_t> t_counts;
  for (auto c : t) {
    t_counts[c]++;
  }
  size_t found_t{0};
  size_t left{0};
  size_t right{0};
  unordered_map<char, size_t> current_window_counts;
  // try to speed up the search by moving to the first match
  while (left < s.size()) {
    if (t_counts.find(s[left]) != t_counts.end()) {
      break;
    }
    ++left;
    ++right;
  }
  size_t unique_t{t_counts.size()};
  size_t ans_l{0};
  size_t min_length{s.size() + 1};
  // find the rest of the matches by expanding to the right
  while (right < s.size()) {
    // add the right most character
    current_window_counts[s[right]]++;
    if (t_counts.find(s[right]) != t_counts.end() &&
        current_window_counts[s[right]] == t_counts[s[right]]) {
      ++found_t;
    }

    // If we have a valid window, then shrink the window from the left
    while (left <= right && found_t == unique_t) {
      // save the current window if it is smaller than the current min
      auto cur_length = right - left + 1;
      if (cur_length < min_length) {
        ans_l = left;
        min_length = cur_length;
      }
      // shrink the window from the left by moving to the left
      current_window_counts[s[left]]--;
      if (t_counts.find(s[left]) != t_counts.end() &&
          current_window_counts[s[left]] < t_counts[s[left]]) {
        --found_t;
      }
      ++left;
    }
    // expand window to the right
    ++right;
  }
  // if we found a valid solution then return it
  if (min_length <= s.size()) {
    return s.substr(ans_l, min_length);
  }
  // if no valid solution then return the empty string
  return "";
}

}  // namespace cpp_practice::cpp_20::min_window