///\file logger.h
///\author Jamie LaPointe (jamie.lapointe@gmail.com)
///\brief Wrap spdlog logging library
///\version 0.1
///\date 2023-09-29
///
///@copyright Copyright (c) 2023
///

#pragma once

#include <fmt/core.h>
#include <spdlog/spdlog.h>

#include "cpp_practice_config.h"

namespace cpp_practice::log {

///\brief Format string type
///
///\tparam Args Variadic template parameter pack representing format values
template <typename... Args>
using Format_String = fmt::format_string<Args...>;

///\brief Log a critical severity message
///\tparam Args Variadic template parameter pack representing format values
///\param fmt Format string
///\param args format values
template <typename... Args>
inline void critical(Format_String<Args...> fmt, Args &&...args) {
  if constexpr (cpp_practice::options::kEnableLogging) {
    if constexpr (sizeof...(args) == 0) {
      spdlog::critical(fmt);
    } else {
      spdlog::critical(fmt, std::forward<Args>(args)...);
    }
  }
}

///\brief Log a error severity message
///\tparam Args Variadic template parameter pack representing format values
///\param fmt Format string
///\param args format values
template <typename... Args>
inline void error(Format_String<Args...> fmt, Args &&...args) {
  if constexpr (cpp_practice::options::kEnableLogging) {
    if constexpr (sizeof...(args) == 0) {
      spdlog::error(fmt);
    } else {
      spdlog::error(fmt, std::forward<Args>(args)...);
    }
  }
}

///\brief Log a warn severity message
///\tparam Args Variadic template parameter pack representing format values
///\param fmt Format string
///\param args format values
template <typename... Args>
inline void warn(Format_String<Args...> fmt, Args &&...args) {
  if constexpr (cpp_practice::options::kEnableLogging) {
    if constexpr (sizeof...(args) == 0) {
      spdlog::warn(fmt);
    } else {
      spdlog::warn(fmt, std::forward<Args>(args)...);
    }
  }
}

///\brief Log a info severity message
///\tparam Args Variadic template parameter pack representing format values
///\param fmt Format string
///\param args format values
template <typename... Args>
inline void info(Format_String<Args...> fmt, Args &&...args) {
  if constexpr (cpp_practice::options::kEnableLogging) {
    if constexpr (sizeof...(args) == 0) {
      spdlog::info(fmt);
    } else {
      spdlog::info(fmt, std::forward<Args>(args)...);
    }
  }
}

///\brief Log a debug severity message
///\tparam Args Variadic template parameter pack representing format values
///\param fmt Format string
///\param args format values
template <typename... Args>
inline void debug(Format_String<Args...> fmt, Args &&...args) {
  if constexpr (cpp_practice::options::kEnableLogging) {
    if constexpr (sizeof...(args) == 0) {
      spdlog::debug(fmt);
    } else {
      spdlog::debug(fmt, std::forward<Args>(args)...);
    }
  }
}

///\brief Log a trace severity message
///\tparam Args Variadic template parameter pack representing format values
///\param fmt Format string
///\param args format values
template <typename... Args>
inline void trace(Format_String<Args...> fmt, Args &&...args) {
  if constexpr (cpp_practice::options::kEnableLogging) {
    if constexpr (sizeof...(args) == 0) {
      spdlog::trace(fmt);
    } else {
      spdlog::trace(fmt, std::forward<Args>(args)...);
    }
  }
}

}  // namespace cpp_practice::log
