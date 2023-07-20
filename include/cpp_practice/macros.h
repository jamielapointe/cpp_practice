///\file macros.h
///\author Jamie LaPointe (jamie.lapointe@gmail.com)
///\brief Provides macros and other preprocessor directives to the rest of the
/// project
///\version 0.1
///\date 2023-07-05
///
///\copyright Copyright (c) 2023
///

// this uses macros... yuck.  Until I discover a better way of doing this
// stuff...

#pragma once

#include "cpp_practice/compiler_macros.h"
#include "cpp_practice/cpp_practice_asserts.h"

/// \internal cpp_practice_HAS_BUILTIN determine is a
/// __builtin_expression is available
#if defined(__has_builtin)
#  define cpp_practice_HAS_BUILTIN(expression) __has_builtin(expression)
#else
#  define cpp_practice_HAS_BUILTIN(expression) 0
#endif

#ifndef cpp_practice_HAS_BUILTIN_FILE
// Clang can check if __builtin_FILE() is supported.
// GCC > 5, MSVC 2019 14.26 (1926) all have __builtin_FILE().
//
// For NVCC, it's more complicated.  Through trial-and-error:
//   - nvcc+gcc supports __builtin_FILE() on host, and on device after CUDA 11.
//   - nvcc+msvc supports __builtin_FILE() only after CUDA 11.
#  if (cpp_practice_HAS_BUILTIN(__builtin_FILE) &&   \
       (cpp_practice_COMP_CLANG ||                   \
        !defined(cpp_practice_CUDA_ARCH))) ||        \
      (cpp_practice_GNUC_STRICT_AT_LEAST(5, 0, 0) && \
       (cpp_practice_COMP_NVCC >= 110000 ||          \
        !defined(cpp_practice_CUDA_ARCH))) ||        \
      (cpp_practice_COMP_MSVC >= 1926 &&             \
       (!cpp_practice_COMP_NVCC ||                   \
        cpp_practice_COMP_NVCC >= 110000))
#    define cpp_practice_HAS_BUILTIN_FILE 1
#  else
#    define cpp_practice_HAS_BUILTIN_FILE 0
#  endif
#endif  // cpp_practice_HAS_BUILTIN_FILE

#if cpp_practice_HAS_BUILTIN_FILE
#  define cpp_practice_BUILTIN_FILE __builtin_FILE()
#  define cpp_practice_BUILTIN_LINE __builtin_LINE()
#else
// Default (potentially unsafe) values.
#  define cpp_practice_BUILTIN_FILE __FILE__
#  define cpp_practice_BUILTIN_LINE __LINE__
#endif

// Use __PRETTY_FUNCTION__ when available, since it is more descriptive, as
// __builtin_FUNCTION() only returns the undecorated function name.
// This should still be okay ODR-wise since it is a compiler-specific fixed
// value.  Mixing compilers will likely lead to ODR violations anyways.
#if cpp_practice_COMP_MSVC
#  define cpp_practice_BUILTIN_FUNCTION \
    static_cast<char const *>(__FUNCSIG__)
#elif cpp_practice_COMP_GNUC
#  define cpp_practice_BUILTIN_FUNCTION \
    static_cast<char const *>(__PRETTY_FUNCTION__)
#else
#  define cpp_practice_BUILTIN_FUNCTION \
    static_cast<char const *>(__func__)
#endif

// clang-format off

// We must define functional macros because as of C++ 20 there is no way to
// perform stringification on an expression other than via a the C preprocessor

#if !defined(_cpp_practice_ASSERT_MESSAGE_DEFINITION)
#  define _cpp_practice_ASSERT_MESSAGE_DEFINITION(expression, message)           \
    {                                                                         \
      if (expression) [[likely]] {                                            \
        static_cast<void>(0);                                                 \
      }                                                                       \
      else {                                                                  \
        cpp_practice::internal::_assert_handler(                                 \
                 #expression, cpp_practice_BUILTIN_FILE, cpp_practice_BUILTIN_LINE, \
                 cpp_practice_BUILTIN_FUNCTION, message);                        \
      }                                                                       \
    }
#endif

#if !defined(_cpp_practice_INTERNAL_ASSERT_MESSAGE_DEFINITION)
#  define _cpp_practice_INTERNAL_ASSERT_MESSAGE_DEFINITION(expression, message)  \
    {                                                                         \
      if (expression) [[likely]] {                                            \
        static_cast<void>(0);                                                 \
      }                                                                       \
      else {                                                                  \
        cpp_practice::internal::_internal_assert_handler(                        \
                 #expression, cpp_practice_BUILTIN_FILE, cpp_practice_BUILTIN_LINE, \
                 cpp_practice_BUILTIN_FUNCTION, message);                        \
      }                                                                       \
    }
#endif

///\brief macro function to run-time error check an expression with a custom error message
#if !defined(cpp_practice_assert_message)
#  define cpp_practice_assert_message(expression, message) _cpp_practice_ASSERT_MESSAGE_DEFINITION(expression, message);  // NOLINT(cppcoreguidelines-macro-usage)
#endif

///\brief macro function to run-time error check an expression
#if !defined(cpp_practice_assert)
#  define cpp_practice_assert(expression) cpp_practice_assert_message(expression, nullptr);  // NOLINT(cppcoreguidelines-macro-usage)
#endif

///\internal macro function to run-time error check an expression with a custom error message
#if !defined(cpp_practice_internal_assert_message)
#  define cpp_practice_internal_assert_message(expression, message) _cpp_practice_INTERNAL_ASSERT_MESSAGE_DEFINITION(expression, message);  // NOLINT(cppcoreguidelines-macro-usage)
#endif

///\internal macro function to run-time error check an expression
#if !defined(cpp_practice_internal_assert)
#  define cpp_practice_internal_assert(expression) cpp_practice_internal_assert_message(expression, nullptr);  // NOLINT(cppcoreguidelines-macro-usage)
#endif

// clang-format on
