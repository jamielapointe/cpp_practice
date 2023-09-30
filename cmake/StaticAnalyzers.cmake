# Enable static analyzers
# Parameters:
#   CPPCHECK_OPTIONS [in] - Optionally override CPPCHECK options; pass in empty
#                           string to stick with default settings
macro(cpp_practice_enable_cppcheck CPPCHECK_OPTIONS)
  find_program(CPPCHECK cppcheck)
  if(CPPCHECK)

    if(CMAKE_GENERATOR MATCHES ".*Visual Studio.*")
      set(CPPCHECK_TEMPLATE "vs")
    else()
      set(CPPCHECK_TEMPLATE "gcc")
    endif()

    if("${CPPCHECK_OPTIONS}" STREQUAL "")
      # Enable all warnings that are actionable by the user of this toolset
      # style should enable the other 3, but we'll be explicit just in case
      set(CMAKE_CXX_CPPCHECK
          ${CPPCHECK}
          --template=${CPPCHECK_TEMPLATE}
          --enable=style,performance,warning,portability
          --inline-suppr
          # We cannot act on a bug/missing feature of cppcheck
          --suppress=cppcheckError
          --suppress=internalAstError
          # if a file does not have an internalAstError, we get an unmatchedSuppression error
          --suppress=unmatchedSuppression
          # noisy and incorrect sometimes
          --suppress=passedByValue
          --suppress=noExplicitConstructor
          # ignores code that cppcheck thinks is invalid C++
          --suppress=syntaxError
          --suppress=preprocessorErrorDirective
          --suppress=unknownMacro
          --inconclusive)
    else()
      # if the user provides a CPPCHECK_OPTIONS with a template specified, it will override this template
      set(CMAKE_CXX_CPPCHECK ${CPPCHECK} --template=${CPPCHECK_TEMPLATE} ${CPPCHECK_OPTIONS})
    endif()

    if(NOT
       "${CMAKE_CXX_STANDARD}"
       STREQUAL
       "")
      set(CMAKE_CXX_CPPCHECK ${CMAKE_CXX_CPPCHECK} --std=c++${CMAKE_CXX_STANDARD})
    endif()
    list(APPEND CMAKE_CXX_CPPCHECK --error-exitcode=2)
  else()
    message(${WARNING_MESSAGE} "cppcheck requested but executable not found")
  endif()
endmacro()

# Enable clang-tidy static analysis checking during build time
# Parameters: <none>
macro(cpp_practice_enable_clang_tidy target)

  find_program(
    CLANGTIDY
    NAMES clang-tidy-16
          clang-tidy-17
          clang-tidy-18
          clang-tidy-19
          clang-tidy)
  if(CLANGTIDY)
    if(NOT
       CMAKE_CXX_COMPILER_ID
       MATCHES
       ".*Clang")

      get_target_property(TARGET_PCH ${target} INTERFACE_PRECOMPILE_HEADERS)

      if("${TARGET_PCH}" STREQUAL "TARGET_PCH-NOTFOUND")
        get_target_property(TARGET_PCH ${target} PRECOMPILE_HEADERS)
      endif()

      if(NOT ("${TARGET_PCH}" STREQUAL "TARGET_PCH-NOTFOUND"))
        message(
          SEND_ERROR
            "clang-tidy cannot be enabled with non-clang compiler and PCH, clang-tidy fails to handle gcc's PCH file")
      endif()
    endif()

    # construct the clang-tidy command line
    set(CLANG_TIDY_OPTIONS
        ${CLANGTIDY}
        -extra-arg=-Wno-unknown-warning-option
        -extra-arg=-Wno-ignored-optimization-argument
        -extra-arg=-Wno-unused-command-line-argument
        "-line-filter=[{'name':'macros.h','lines':[[999999,999999]]}]"
        -p
        ${cpp_practice_BUILD_ROOT})

    message("Also setting clang-tidy globally")
    set(CMAKE_CXX_CLANG_TIDY ${CLANG_TIDY_OPTIONS})
  else()
    message(${WARNING_MESSAGE} "clang-tidy requested but executable not found")
  endif()
endmacro()

# Enable the include what use use check
macro(cpp_practice_enable_include_what_you_use)
  find_program(INCLUDE_WHAT_YOU_USE include-what-you-use)
  if(INCLUDE_WHAT_YOU_USE)
    set(CMAKE_CXX_INCLUDE_WHAT_YOU_USE ${INCLUDE_WHAT_YOU_USE})
  else()
    message(${WARNING_MESSAGE} "include-what-you-use requested but executable not found")
  endif()
endmacro()
