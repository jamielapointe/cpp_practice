///\file reverse_words.h
///\author Jamie LaPointe (jamie.lapointe@gmail.com)
///\brief LeetCode 151. Reverse Words in a String
///\version 0.1
///\date 2023-07-30
///
///\details Given an input string s, reverse the order of the words.
/// A word is defined as a sequence of non-space characters. The words in s will
/// be separated by at least one space. Return a string of the words in reverse
/// order concatenated by a single space.
///\note that s may contain leading or
/// trailing spaces or multiple spaces between two words. The returned string
/// should only have a single space separating the words. Do not include any
/// extra spaces.
///@copyright Copyright (c) 2023
///

#pragma once

#include <regex>
#include <string>

namespace cpp_practice::cpp_20::reverse_words {

std::string reverseWordsSlowRegex(std::string s) {
  // collect all of the words in the string
  std::regex word_regex(R"(\w+)");
  auto words_begin = std::sregex_iterator(s.begin(), s.end(), word_regex);
  auto words_end = std::sregex_iterator();
  std::stack<std::string> words;
  // reverse the order of the words
  for (; words_begin != words_end; ++words_begin) {
    words.push((*words_begin)[0]);
  }
  // build the string
  std::ostringstream reverse_words;
  if (!words.empty()) {
    reverse_words << words.top();
    words.pop();
  }
  while (!words.empty()) {
    reverse_words << " " << words.top();
    words.pop();
  }
  return reverse_words.str();
}

std::string reverseWordsStringStream(std::string s) {
  // string stream method
  std::istringstream ss(s);
  std::vector<std::string> words;
  std::string word;
  while (ss >> word) {
    words.emplace_back(word);
  }
  std::ostringstream ss1;
  int index{static_cast<int>(words.size()) - 1};
  if (words.size() > 0) {
    ss1 << words[static_cast<size_t>(index--)];
  }
  for (; index > -1; --index) {
    ss1 << " " << words[static_cast<size_t>(index)];
  }
  return ss1.str();
}

}  // namespace cpp_practice::cpp_20::reverse_words
