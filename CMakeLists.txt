#Definition CMake version
cmake_minimum_required(VERSION 2.8)

project(foeb CXX)

set(CMAKE_CXX_STANDARD 11)

if(WIN32)
    set(EXTENSION ".exe")
else()
    set(EXTENSION "")
endif()

set(OUTPUT_NAME "${PROJECT_NAME}${EXTENSKION}")

include_directories(
	./
)

add_executable(
    ${OUTPUT_NAME}
    src/main.cpp
    src/ArgsAnalyzer.cpp
)

