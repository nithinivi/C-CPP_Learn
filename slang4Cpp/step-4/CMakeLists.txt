cmake_minimum_required(VERSION 3.16)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# set the project name and version
project(slang VERSION 4.0)

# inserting values to vars
configure_file(
  slang/include/SlangConfig.h
  SlangConfig.h
)

file(GLOB_RECURSE SRC_FILES slang/*.cpp)
add_executable(slang ${SRC_FILES})

target_include_directories(
  slang
  PUBLIC
  "${PROJECT_BINARY_DIR}"
)

# specify the C++ standard
