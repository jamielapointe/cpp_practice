
#include <gtest/gtest.h>

#include "cpp_practice/expects.h"

using cpp_practice::Error_Code;
using cpp_practice::expect;
using cpp_practice::internal::do_log_error;
using cpp_practice::internal::log_error;
using cpp_practice::options::Error_Action;

TEST(TestExpects, TestDoLogError) {
  EXPECT_TRUE(do_log_error<Error_Action::kAbort>());
  EXPECT_TRUE(do_log_error<Error_Action::kTerminate>());
  EXPECT_TRUE(do_log_error<Error_Action::kThrow>());
  EXPECT_FALSE(do_log_error<Error_Action::kIgnore>());
}

namespace {

void test_log_error(
    Error_Code error_code, std::string_view message,
    std::source_location location = std::source_location::current()) {
  log_error(error_code, location.file_name(), location.line(),
            location.column(), location.function_name(), message);
}

bool test_condition() { return false; }
}  // namespace

TEST(TestExpects, TestLogError) {
  Error_Code error_code{Error_Code::kRangeError};
  std::string_view message{"Test message"};
  test_log_error(error_code, message);
}

TEST(TestExpects, TestExpectError) {
  Error_Code error_code{Error_Code::kRangeError};
  std::string_view message{"Test message"};

  EXPECT_ANY_THROW(
      expect<Error_Action::kAbort>(test_condition, error_code, message));
  EXPECT_ANY_THROW(
      expect<Error_Action::kTerminate>(test_condition, error_code, message));
  EXPECT_ANY_THROW(
      expect<Error_Action::kThrow>(test_condition, error_code, message));
  EXPECT_NO_THROW(
      expect<Error_Action::kIgnore>(test_condition, error_code, message));
}
