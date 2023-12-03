#include <gtest/gtest.h>

#include <array>
#include <cstddef>

#include "cpp_practice/endianess.h"

namespace {

struct EndianCheck {
  bool is_big_endian() {
    int the_integer = 1;
    auto bytes = std::bit_cast<std::array<std::byte, sizeof(int)>>(the_integer);
    return bytes[0] == std::byte{0};
  }
};

TEST(
    EndianessTest,
    Test0) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  EXPECT_EQ(cpp_practice::endianess::is_little_endian(),
            !EndianCheck().is_big_endian());
  EXPECT_EQ(cpp_practice::endianess::is_big_endian(),
            EndianCheck().is_big_endian());
  EXPECT_EQ(cpp_practice::endianess::get_endianess(),
            cpp_practice::endianess::endianess::little_endian);
}

}  // namespace
