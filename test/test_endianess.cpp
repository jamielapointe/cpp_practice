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

  cpp_practice::endianess::endianess get_endianess() {
    if (is_big_endian()) {
      return cpp_practice::endianess::endianess::big_endian;
    }

    return cpp_practice::endianess::endianess::little_endian;
  }
};

TEST(
    EndianessTest,
    TestEndianess) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  EXPECT_EQ(cpp_practice::endianess::is_little_endian(),
            !EndianCheck().is_big_endian());
  EXPECT_EQ(cpp_practice::endianess::is_big_endian(),
            EndianCheck().is_big_endian());
  EXPECT_EQ(cpp_practice::endianess::get_endianess(),
            EndianCheck().get_endianess());
}

#if defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_BIG_ENDIAN__)
TEST(
    EndianessTest,
    TestBigEndian) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  EXPECT_FALSE(cpp_practice::endianess::is_little_endian());
  EXPECT_TRUE(cpp_practice::endianess::is_big_endian());
  EXPECT_EQ(cpp_practice::endianess::get_endianess(),
            cpp_practice::endianess::endianess::big_endian);
}
#elif defined(__BYTE_ORDER__) && (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__)
TEST(
    EndianessTest,
    TestLittleEndian) {  // NOLINT(cppcoreguidelines-avoid-non-const-global-variables,cppcoreguidelines-owning-memory)
  EXPECT_TRUE(cpp_practice::endianess::is_little_endian());
  EXPECT_FALSE(cpp_practice::endianess::is_big_endian());
  EXPECT_EQ(cpp_practice::endianess::get_endianess(),
            cpp_practice::endianess::endianess::little_endian);
}
#endif

// we do not support the PDP-11 architecture, so I suppose we can ignore mixed
// endianess for this test

}  // namespace
