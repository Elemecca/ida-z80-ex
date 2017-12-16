cmake_minimum_required(VERSION 3.5)

project(ida-z80-ex CXX)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/build")


list(APPEND CMAKE_MODULE_PATH external/cmake-ida)
find_package(IDA 7.0 MODULE REQUIRED)

add_ida_module(z80-ex PROCESSOR SOURCES
    src/module.cpp
    src/assemblers.cpp
    src/registers.cpp
    src/instructions.cpp
    src/analyze.cpp
)
