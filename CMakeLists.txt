cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MyProject VERSION 1.0)

# Set C++ standard (optional but recommended)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Collect source files
set(SOURCES
    v1.5.cpp
    helper.cpp
    helperFunctions.cpp
    cFunctions.tpp
)

# Create executable
add_executable(MyExecutable ${SOURCES})

# Optional: Include directories if needed
# include_directories(${CMAKE_SOURCE_DIR}/include)

# Output information
message(STATUS "Building MyExecutable from ${SOURCES}")

# Enable extra warnings (optional but useful)
target_compile_options(MyExecutable PRIVATE -Wall -Wextra -Wpedantic -O3)
