cmake_minimum_required(VERSION 3.16)

project(TaskProcessingEngine
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(FetchContent)

FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.17.0.zip
    DOWNLOAD_EXTRACT_TIMESTAMP TRUE
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_library(ThreadPool
    src/ThreadPool.cpp
)

target_include_directories(ThreadPool
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(TaskProcessingEngine
    examples/main.cpp
)

target_link_libraries(TaskProcessingEngine
    PRIVATE
        ThreadPool
)

enable_testing()

add_executable(ThreadPoolTests
    tests/ThreadPoolTests.cpp
)

target_link_libraries(ThreadPoolTests
    PRIVATE
        ThreadPool
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(ThreadPoolTests)