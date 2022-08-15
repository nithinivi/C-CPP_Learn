cmake_minimum_required(VERSION 3.16.3)

# set the project name
project(slangLLvm VERSION 1.0 LANGUAGES CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)


add_subdirectory(contexts)
add_subdirectory(ast)
add_subdirectory(frontend)
add_subdirectory(callSlang)
