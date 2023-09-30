#include <gtest/gtest.h>

#include "cpp_practice/cpp_practice_asserts.h"
#include "cpp_practice/log/logger.h"

using cpp_practice::internal::print_error;
using cpp_practice::log::critical;
using cpp_practice::log::debug;
using cpp_practice::log::error;
using cpp_practice::log::info;
using cpp_practice::log::trace;
using cpp_practice::log::warn;

// TODO(jlapointe) Validate the output of the logger

TEST(TestLogger, TestLogger) {
  critical("This is a critical message");
  debug("This is a debug message");
  error("This is an error message");
  info("This is an info message");
  trace("This is a trace message");
  warn("This is a warn message");
}

TEST(TestLogger, TestPrintError) {
  print_error("expression", "file", 1, "function", "message");
}
