cmake_minimum_required(VERSION 3.16)

project(TaskProcessingEngine
    VERSION 1.0
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(TaskProcessingEngine
    examples/main.cpp
    src/ThreadPool.cpp
)

target_include_directories(TaskProcessingEngine
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)