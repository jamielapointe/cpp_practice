cmake_minimum_required(VERSION 3.25)

project(CmakeConfigPackageTests LANGUAGES CXX)

# ---- Test as standalone project the exported config package ----

if(PROJECT_IS_TOP_LEVEL OR TEST_INSTALLED_VERSION)
  enable_testing()

  find_package(cpp_practice CONFIG REQUIRED) # for intro, project_options, ...

  if(NOT TARGET cpp_practice_options)
    message(FATAL_ERROR "Required config package not found!")
    return() # be strictly paranoid for Template Janitor github action! CK
  endif()
endif()

# ---- Dependencies ----

add_executable(
  cpp_practice_tests
  test_binary_exponentiation.cpp
  test_breadth_first_search_unordered.cpp
  test_endianess.cpp
  test_factorial.cpp
  test_fibonacci.cpp
  test_length_of_longest_substring.cpp
  test_list_sum_with_mask.cpp
  test_logging.cpp
  test_main.cpp
  test_min_window.cpp
  test_path_through_the_maze.cpp
  test_pattern_matching_0.cpp
  test_reverse_words.cpp)
target_include_directories(cpp_practice_tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${cpp_practice_ROOT}/include
                                                      ${cpp_practice_BUILD_ROOT}/configured_files/include)
target_link_libraries(cpp_practice_tests PRIVATE cpp_practice::cpp_practice_options cpp_practice::cpp_practice_warnings)
target_link_system_libraries(
  cpp_practice_tests
  PRIVATE
  GTest::gtest_main
  fmt::fmt
  spdlog::spdlog
  Microsoft.GSL::GSL)

include(GoogleTest)
gtest_discover_tests(cpp_practice_tests XML_OUTPUT_DIR ${CMAKE_BINARY_DIR})
