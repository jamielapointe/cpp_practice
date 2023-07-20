# A very simple example of a configured file that might need to be
# converted to one that is publicly installed in the case that
# you are developing a library
configure_file("cpp_practice_config.h.in"
               "${cpp_practice_BUILD_ROOT}/configured_files/include/cpp_practice_config.h" ESCAPE_QUOTES)
