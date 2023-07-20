if(TARGET cpp_practice_benchmark)
  target_sources(cpp_practice_benchmark PUBLIC benchmark_main.cpp bm_fibonacci.cpp)

  # target_compile_options(cpp_practice_benchmark PRIVATE -fno-exceptions)
  target_compile_options(cpp_practice_benchmark PRIVATE -Wno-weak-vtables)
  target_compile_options(cpp_practice_benchmark PRIVATE -Wno-global-constructors)
  target_compile_options(cpp_practice_benchmark PRIVATE -Wno-unused-member-function)

  target_include_directories(cpp_practice_benchmark SYSTEM PRIVATE "${benchmark_SOURCE_DIR}/include")

  target_link_system_libraries(cpp_practice_benchmark PRIVATE benchmark::benchmark)
endif()
