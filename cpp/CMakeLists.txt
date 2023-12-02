cmake_minimum_required(VERSION 3.27)
project(aoc2023)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.14.0
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(aoc2023_tests
    main.cpp
    utility.hpp
    day1.hpp
    day2.hpp)

set_target_properties(aoc2023_tests PROPERTIES CXX_STANDARD 23)

target_link_libraries(aoc2023_tests PRIVATE
    gtest
    gmock)

include(GoogleTest)
gtest_discover_tests(aoc2023_tests)
