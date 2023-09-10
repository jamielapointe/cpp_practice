
#include <gtest/gtest.h>

#include <array>
#include <cstdint>

#include "cpp_practice/bit_manipulations/pattern_matching_0.h"

using cpp_practice::bit_manipulations::pattern_matching_0::find_pattern;

// NOLINTBEGIN(cppcoreguidelines-avoid-magic-numbers)

// [1111 1111, 1111 1111, 0000 0000, 0110 0101, 0100 0011, 0010 0001, 1111 1111]
//                        ^                                        ^
TEST(PatternMatching0Test, Test00) {
  uint32_t pattern = 0x00654321;
  std::array<uint8_t, 7> array = {0xFF, 0xFF, 0x00, 0x65, 0x43, 0x21, 0xFF};
  int expected = 16;
  int result = find_pattern<7>(pattern, array);
  EXPECT_EQ(result, expected);
}

// [1111 1111, 1111 1110, 0000 0000, 1100 1010, 1000 0110, 0100 0011, 1111 1111]
//                     ^                                          ^
TEST(PatternMatching0Test, Test01) {
  uint32_t pattern = 0x00654321;
  std::array<uint8_t, 7> array = {0xFF, 0xFE, 0x00, 0xCA, 0x86, 0x43, 0xFF};
  int expected = 15;
  int result = find_pattern<7>(pattern, array);
  EXPECT_EQ(result, expected);
}

// NOLINTEND(cppcoreguidelines-avoid-magic-numbers)
