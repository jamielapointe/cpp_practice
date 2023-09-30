///\brief Provide configurable expects functions for the project
///
/// Provides runtime verification of function invariance.  Whenever possible
/// utilize static_asserts and concepts to verify invariance at compile time.
///
/// \note \c Error_Action is defined in cpp_practice_config.h.in
/// \note \c kDefaultErrorAction is defined in cpp_practice_config.h.in and is
/// user configurable via CMake
///

#include <array>
#include <source_location>
#include <string_view>

#include "cpp_practice_config.h"
#include "log/logger.h"

namespace cpp_practice {

///\brief Possible error codes for expects
enum class Error_Code {
  kRangeError,
  kLengthError,
  kNullptrError,
  kInvalidArgumentError,

  // kSize must be the last entry to allow for constexpr array sizing
  kSize
};  // namespace cpp_practice

inline constexpr std::array<std::string_view,
                            static_cast<size_t>(Error_Code::kSize)>
    kErrorCodeNames = {"RangeError", "LengthError", "NullptrError",
                       "InvalidArgumentError"};
static_assert(kErrorCodeNames.size() == static_cast<size_t>(Error_Code::kSize),
              "kErrorCodeNames must have the same number of elements as "
              "Error_Code has enumerators");

namespace internal {

template <options::Error_Action action>
inline constexpr bool do_log_error() {
  return action == options::Error_Action::kAbort ||
         action == options::Error_Action::kTerminate ||
         action == options::Error_Action::kThrow;
}

inline void log_error(Error_Code error_code, std::string_view file_name,
                      uint_least32_t line, uint_least32_t column,
                      std::string_view function_name,
                      std::string_view message) {
  cpp_practice::log::critical(
      "Expectation with error_code {} [ {} ] failed at file {} ({}:{}) `{}`"
      "{}",
      static_cast<int>(error_code),
      kErrorCodeNames.at(static_cast<size_t>(error_code)), file_name, line,
      column, function_name,
      message.size() > 0 ? fmt::format(" with message: {}", message) : "");
}

}  // namespace internal

template <options::Error_Action action = options::kDefaultErrorAction,
          typename Condition_T>
inline void expect(
    Condition_T condition, Error_Code error_code, std::string_view message = "",
    std::source_location location = std::source_location::current()) {
  if constexpr (internal::do_log_error<action>()) {
    if (!condition()) {
      internal::log_error(error_code, location.file_name(), location.line(),
                          location.column(), location.function_name(), message);
      if constexpr (action == options::Error_Action::kAbort) {
        std::abort();
      }
      if constexpr (action == options::Error_Action::kTerminate) {
        std::terminate();
      }
      if constexpr (action == options::Error_Action::kThrow) {
        throw error_code;
      }
    }
  }
  // Else no action
}

}  // namespace cpp_practice