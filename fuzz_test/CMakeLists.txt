# A fuzz test runs until it finds an error. This particular one is going to rely on libFuzzer.
#

find_package(fmt)

target_sources(cpp_practice_fuzz_tester PUBLIC fuzz_tester.cpp)

target_link_libraries(cpp_practice_fuzz_tester PRIVATE fmt::fmt -fsanitize=fuzzer)
target_compile_options(cpp_practice_fuzz_tester PRIVATE -fsanitize=fuzzer)
if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_compile_options(cpp_practice_fuzz_tester PRIVATE --coverage)
  target_link_libraries(cpp_practice_fuzz_tester PRIVATE --coverage)
endif()
if(CMAKE_CXX_COMPILER_ID MATCHES ".*Clang")
  target_compile_options(cpp_practice_fuzz_tester PRIVATE -fprofile-instr-generate -fcoverage-mapping)
  target_link_libraries(cpp_practice_fuzz_tester PRIVATE -fprofile-instr-generate -fcoverage-mapping)
endif()

# Allow short runs during automated testing to see if something new breaks
set(FUZZ_RUNTIME
    10
    CACHE STRING "Number of seconds to run fuzz tests during ctest run") # Default of 10 seconds

add_test(NAME cpp_practice_fuzz_tester_run COMMAND cpp_practice_fuzz_tester
                                                          -max_total_time=${FUZZ_RUNTIME})
