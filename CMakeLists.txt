#Definition CMake version
cmake_minimum_required(VERSION 2.8)

project(fbep CXX)

set(CMAKE_CXX_STANDARD 14)

if(WIN32)
    set(EXTENSION ".exe")
else()
    set(EXTENSION "")
endif()

set(OUTPUT_NAME "${PROJECT_NAME}${EXTENSKION}")

add_executable(
    ${OUTPUT_NAME}
    src/main.cpp
    src/ArgsAnalyzer.cpp
)

