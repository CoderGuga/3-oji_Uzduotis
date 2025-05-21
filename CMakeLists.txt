cmake_minimum_required(VERSION 3.10)

project(MyProject VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files for main executable
set(SOURCES
    main.cpp
    Vector.tpp
)

add_executable(test_exe ${SOURCES})
target_compile_options(test_exe PRIVATE -Wall -Wextra -Wpedantic -O0)

# Source files for main executable
set(SOURCES2
    v3.0.cpp
    helper.cpp
    helperFunctions.cpp
    cFunctions.tpp
    Vector.tpp
)

add_executable(main_exe ${SOURCES2})
target_compile_options(main_exe PRIVATE -Wall -Wextra -Wpedantic -O0)