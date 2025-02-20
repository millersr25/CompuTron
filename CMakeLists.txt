cmake_minimum_required(VERSION 3.10)

# Set the C++ standard to C++23
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# used internally by CMake to identify your project
project(CompuTron)

# Include the directory headers are located 
include_directories(${CMAKE_SOURCE_DIR})

# Add the main executable
add_executable(compuTron main.cpp computron.cpp)

# Add the test executable 
add_executable(compuTronTest  computron.cpp test.cpp)

# Include directories for the movie executable
target_include_directories(compuTron PRIVATE ${PROJECT_SOURCE_DIR})

# Include directories for the test Target 
target_include_directories(compuTronTest PRIVATE ${PROJECT_SOURCE_DIR})

# Enable testing
enable_testing()

# Register the test executable with CTest (optional)
add_test(NAME compuTronTest COMMAND compuTronTest)
