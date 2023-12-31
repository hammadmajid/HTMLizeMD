cmake_minimum_required(VERSION 3.27)
project(HTMLizeMD)

set(CMAKE_CXX_STANDARD 23)

# Use FetchContent to download and include Google Test
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# Ensure GoogleTest uses a shared CRT
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Include directories for the main project and Google Test
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/test)

# Enable testing
enable_testing()

# Add the main project executable
add_executable(HTMLizeMD
        src/main.cpp
        src/clap.h
        src/lexer.h
        src/generator.h)

# Add the test executable
add_executable(HTMLizeMDTests tests/clap_test.cpp)

# Link the main project executable against the Google Test library
target_link_libraries(HTMLizeMDTests GTest::gtest_main)

# Use GoogleTest to discover tests
include(GoogleTest)
gtest_discover_tests(HTMLizeMDTests)
