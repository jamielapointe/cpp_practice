include(SystemLink)
include(LibFuzzer)
include(CMakeDependentOption)
include(CheckCXXCompilerFlag)

# Test if compiler supports Sanitizers
# Parameters: <none>
macro(cpp_practice_supports_sanitizers)
  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND NOT WIN32)
    set(SUPPORTS_UBSAN ON)
  else()
    set(SUPPORTS_UBSAN OFF)
  endif()

  if((CMAKE_CXX_COMPILER_ID MATCHES ".*Clang.*" OR CMAKE_CXX_COMPILER_ID MATCHES ".*GNU.*") AND WIN32)
    set(SUPPORTS_ASAN OFF)
  else()
    set(SUPPORTS_ASAN ON)
  endif()
endmacro()

# Set up user configurable CMake options
# Parameters: <none>
macro(cpp_practice_setup_options)
  if(CMAKE_BUILD_TYPE STREQUAL "Release" OR CMAKE_BUILD_TYPE STREQUAL "MinSizeRel")
    set(DEFAULT_HARDENING ON)
    set(DEFAULT_IPO ON)
    set(DEFAULT_PFM ON)
    set(DEFAULT_ASAN OFF)
    set(DEFAULT_UBSAN OFF)
  else()
    set(DEFAULT_HARDENING OFF)
    set(DEFAULT_IPO OFF)
    set(DEFAULT_PFM OFF)
    set(DEFAULT_ASAN ${SUPPORTS_ASAN})
    set(DEFAULT_UBSAN ${SUPPORTS_UBSAN})
  endif()

  option(cpp_practice_ENABLE_HARDENING "Enable hardening" ${DEFAULT_HARDENING})
  option(cpp_practice_ENABLE_COVERAGE "Enable coverage reporting" OFF)

  cpp_practice_supports_sanitizers()

  # adjust as needed; pretty sure we need 1.9.7 to get the MathJax3 and chtml support
  # not sure about an upper limit...
  find_package(Doxygen 1.9.7...<2.0 OPTIONAL_COMPONENTS dot)
  if(Doxygen_FOUND)
    set(DEFAULT_DOXYGEN ON)
  else()
    set(DEFAULT_DOXYGEN OFF)
  endif()

  set(ERROR_ACTIONS
      IGNORE
      THROW
      ABORT
      TERMINATE)
  if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(DEFAULT_ERROR_ACTION THROW)
  else()
    set(DEFAULT_ERROR_ACTION ABORT)
  endif()
  set(cpp_practice_DEFAULT_ERROR_ACTION
      ${DEFAULT_ERROR_ACTION}
      CACHE STRING "Default error action")
  set_property(CACHE cpp_practice_DEFAULT_ERROR_ACTION PROPERTY STRINGS ${ERROR_ACTIONS})
  list(
    FIND
    ERROR_ACTIONS
    ${cpp_practice_DEFAULT_ERROR_ACTION}
    ERROR_ACTION_INDEX)

  if(NOT PROJECT_IS_TOP_LEVEL)
    option(cpp_practice_BUILD_DOCUMENTATION "Generate Doxygen documentation" OFF)
    option(cpp_practice_ENABLE_IPO "Enable IPO/LTO" OFF)
    option(cpp_practice_ENABLE_LIBPFM "Enable additional performance metrics counters by libpfm" OFF)
    option(cpp_practice_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(cpp_practice_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" OFF)
    option(cpp_practice_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" OFF)
    option(cpp_practice_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" OFF)
    option(cpp_practice_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(cpp_practice_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(cpp_practice_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(cpp_practice_ENABLE_CLANG_TIDY "Enable clang-tidy" OFF)
    option(cpp_practice_ENABLE_CPPCHECK "Enable cpp-check analysis" OFF)
    option(cpp_practice_ENABLE_PCH "Enable precompiled headers" OFF)
    option(cpp_practice_ENABLE_CACHE "Enable ccache" OFF)
    option(cpp_practice_ENABLE_SAMPLE_BASED_PROFILING "Enable sample based profiling" OFF)
    option(cpp_practice_ENABLE_INSTRUMENTED_PROFILING "Enable instrumented based profiling" OFF)
    option(cpp_practice_ENABLE_INTERNAL_DEBUGGING "Enable internal debugging - this is for testing this project only"
           OFF)
    option(cpp_practice_ENABLE_SIMD "Enable SIMD optimizations" OFF)
    option(cpp_practice_ENABLE_DOXYGEN_WITH_CLANG "You have a version of doxygen that does supports clang" OFF)
    option(
      cpp_practice_ENABLE_NATIVE_ARCHITECTURE
      "Enable native architecture optimizations - warning may break if run on older hardware architectures or cross compiling!"
      OFF)
  else()
    option(cpp_practice_BUILD_DOCUMENTATION "Generate Doxygen documentation" ${DEFAULT_DOXYGEN})
    option(cpp_practice_ENABLE_IPO "Enable IPO/LTO" ${DEFAULT_IPO})
    option(cpp_practice_ENABLE_LIBPFM "Enable additional performance metrics counters by libpfm" ${DEFAULT_PFM})
    option(cpp_practice_ENABLE_USER_LINKER "Enable user-selected linker" OFF)
    option(cpp_practice_ENABLE_SANITIZER_ADDRESS "Enable address sanitizer" ${DEFAULT_ASAN})
    option(cpp_practice_ENABLE_SANITIZER_LEAK "Enable leak sanitizer" ${DEFAULT_ASAN})
    option(cpp_practice_ENABLE_SANITIZER_UNDEFINED "Enable undefined sanitizer" ${DEFAULT_UBSAN})
    option(cpp_practice_ENABLE_SANITIZER_THREAD "Enable thread sanitizer" OFF)
    option(cpp_practice_ENABLE_SANITIZER_MEMORY "Enable memory sanitizer" OFF)
    option(cpp_practice_ENABLE_UNITY_BUILD "Enable unity builds" OFF)
    option(cpp_practice_ENABLE_CLANG_TIDY "Enable clang-tidy" ON)
    option(cpp_practice_ENABLE_CPPCHECK "Enable cpp-check analysis" ON)
    option(cpp_practice_ENABLE_PCH "Enable precompiled headers" OFF)
    option(cpp_practice_ENABLE_CACHE "Enable ccache" ON)
    option(cpp_practice_ENABLE_SAMPLE_BASED_PROFILING "Enable sample based profiling" OFF)
    option(cpp_practice_ENABLE_INSTRUMENTED_PROFILING "Enable instrumented based profiling" OFF)
    option(cpp_practice_ENABLE_INTERNAL_DEBUGGING "Enable internal debugging - this is for testing this project only"
           ON)
    option(cpp_practice_ENABLE_SIMD "Enable SIMD optimizations" OFF)
    option(
      cpp_practice_ENABLE_NATIVE_ARCHITECTURE
      "Enable native architecture optimizations - warning may break if run on older hardware architectures or cross compiling!"
      OFF)
    option(
      cpp_practice_ENABLE_DOXYGEN_WITH_CLANG
      "Enable if you have a version of doxygen that was linked with the clang 16.0+ library; this is useful for getting better parsing of C++ code"
      OFF)
  endif()

  if(NOT PROJECT_IS_TOP_LEVEL)
    mark_as_advanced(
      cpp_practice_ENABLE_IPO
      cpp_practice_ENABLE_USER_LINKER
      cpp_practice_ENABLE_SANITIZER_ADDRESS
      cpp_practice_ENABLE_SANITIZER_LEAK
      cpp_practice_ENABLE_SANITIZER_UNDEFINED
      cpp_practice_ENABLE_SANITIZER_THREAD
      cpp_practice_ENABLE_SANITIZER_MEMORY
      cpp_practice_ENABLE_UNITY_BUILD
      cpp_practice_ENABLE_CLANG_TIDY
      cpp_practice_ENABLE_CPPCHECK
      cpp_practice_ENABLE_COVERAGE
      cpp_practice_ENABLE_PCH
      cpp_practice_ENABLE_CACHE
      cpp_practice_ENABLE_SAMPLE_BASED_PROFILING
      cpp_practice_ENABLE_INSTRUMENTED_PROFILING
      cpp_practice_ENABLE_SIMD
      cpp_practice_ENABLE_NATIVE_ARCHITECTURE
      cpp_practice_ENABLE_DOXYGEN_WITH_CLANG)
  endif()

  cpp_practice_check_libfuzzer_support(LIBFUZZER_SUPPORTED)
  if(LIBFUZZER_SUPPORTED AND (cpp_practice_ENABLE_SANITIZER_ADDRESS OR cpp_practice_ENABLE_SANITIZER_UNDEFINED))
    set(DEFAULT_FUZZER ON)
  else()
    set(DEFAULT_FUZZER OFF)
  endif()

  option(cpp_practice_BUILD_FUZZ_TESTS "Enable fuzz testing executable" ${DEFAULT_FUZZER})

endmacro()

# Setup the global options - effects cpp_practice targets as well as third party
# dependencies
macro(cpp_practice_global_options)
  if(cpp_practice_ENABLE_IPO)
    include(InterproceduralOptimization)
    cpp_practice_enable_ipo()
  endif()

  include(Profiling)
  if(cpp_practice_ENABLE_SAMPLE_BASED_PROFILING)
    cpp_practice_enable_sample_based_profiling()
  endif()
  if(cpp_practice_ENABLE_INSTRUMENTED_PROFILING)
    cpp_practice_enable_instrumented_profiling()
  endif()

  cpp_practice_supports_sanitizers()
endmacro()

# Setup the local options - only affects cpp_practice targets
macro(cpp_practice_local_options)
  # setup the fake targets that store the common compiler settings
  add_library(cpp_practice_warnings INTERFACE)
  add_library(cpp_practice::cpp_practice_warnings ALIAS cpp_practice_warnings)

  add_library(cpp_practice_options INTERFACE)
  add_library(cpp_practice::cpp_practice_options ALIAS cpp_practice_options)
  target_compile_features(cpp_practice_options INTERFACE cxx_std_${CMAKE_CXX_STANDARD})

  if(PROJECT_IS_TOP_LEVEL)
    include(CompilerSettings)
  endif()

  include(CompilerWarnings)
  cpp_practice_set_project_warnings(cpp_practice_warnings)

  if(cpp_practice_ENABLE_USER_LINKER)
    include(Linker)
    configure_linker(cpp_practice_options)
  endif()

  include(Sanitizers)
  cpp_practice_enable_sanitizers(
    cpp_practice_options
    ${cpp_practice_ENABLE_SANITIZER_ADDRESS}
    ${cpp_practice_ENABLE_SANITIZER_LEAK}
    ${cpp_practice_ENABLE_SANITIZER_UNDEFINED}
    ${cpp_practice_ENABLE_SANITIZER_THREAD}
    ${cpp_practice_ENABLE_SANITIZER_MEMORY})

  if(cpp_practice_ENABLE_LIBPFM)
    find_package(PFM)
    if(HAVE_PFM)
      target_link_libraries(cpp_practice_options PRIVATE pfm)
    endif()
  endif()

  set_target_properties(cpp_practice_options PROPERTIES UNITY_BUILD ${cpp_practice_ENABLE_UNITY_BUILD})

  if(cpp_practice_ENABLE_PCH)
    target_precompile_headers(
      cpp_practice_options
      INTERFACE
      <vector>
      <string>
      <utility>)
  endif()

  if(cpp_practice_ENABLE_CACHE)
    include(CCache)
    cpp_practice_enable_cache()
  endif()

  include(StaticAnalyzers)
  if(cpp_practice_ENABLE_CLANG_TIDY)
    cpp_practice_enable_clang_tidy(cpp_practice_options)
  endif()

  if(cpp_practice_ENABLE_CPPCHECK)
    # Use Default CPPCHECK settings
    # otherwise pass in string of your own settings
    cpp_practice_enable_cppcheck("")
  endif()

  if(cpp_practice_ENABLE_COVERAGE)
    cpp_practice_enable_coverage(cpp_practice_options)
  endif()

  if(cpp_practice_BUILD_DOCUMENTATION)
    include(Doxygen)
    cpp_practice_enable_doxygen("")
  endif()

  check_cxx_compiler_flag("-Wl,--fatal-warnings" LINKER_FATAL_WARNINGS)
  if(LINKER_FATAL_WARNINGS)
    # This is not working consistently, so disabling for now
    # target_link_options(cpp_practice_options INTERFACE -Wl,--fatal-warnings)
  endif()

  if(cpp_practice_ENABLE_HARDENING)
    include(Hardening)
    if(NOT SUPPORTS_UBSAN
       OR cpp_practice_ENABLE_SANITIZER_UNDEFINED
       OR cpp_practice_ENABLE_SANITIZER_ADDRESS
       OR cpp_practice_ENABLE_SANITIZER_THREAD
       OR cpp_practice_ENABLE_SANITIZER_LEAK)
      set(ENABLE_UBSAN_MINIMAL_RUNTIME FALSE)
    else()
      set(ENABLE_UBSAN_MINIMAL_RUNTIME TRUE)
    endif()
    cpp_practice_enable_hardening(cpp_practice_options ${ENABLE_UBSAN_MINIMAL_RUNTIME})
  endif()

endmacro()
