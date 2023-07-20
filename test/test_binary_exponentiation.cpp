#include <gtest/gtest.h>

#include "cpp_practice/binary_exponentiation.h"

using cpp_practice::algorithms::binary_exponentiation;

TEST(BinaryExponentiation, TestLargeExponentsModuloNumber00) {
  ASSERT_EQ(binary_exponentiation(2, -5, 3), 1);
  ASSERT_EQ(binary_exponentiation(2, 0, 3), 1);
  ASSERT_EQ(binary_exponentiation(2, 5, 7), 4);
  ASSERT_EQ(binary_exponentiation(2, 5, -7), 4);
  ASSERT_EQ(binary_exponentiation(-2, 5, -7), -4);
  ASSERT_EQ(binary_exponentiation(15, 256, 35), 15);
  ASSERT_EQ(binary_exponentiation(-15, 256, 35), 15);
}
