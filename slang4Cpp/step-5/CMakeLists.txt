cmake_minimum_required(VERSION 3.0.0)
project(slang-step-5 VERSION 0.1.0)

set(CMAKE_CXX_COMPILER "/usr/bin/clang++-14")
set(CMAKE_C_COMPILER "/usr/bin/clang-14")
set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_INSTALL_PREFIX "/usr/include/llvm-14")

message("The value of CMAKE_CXX_COMPILER = ${CMAKE_CXX_COMPILER}")
include(CTest)
enable_testing()

configure_file(
    slang/include/SlangConfig.h
    SlangConfig.h
)

file(GLOB_RECURSE SRC_FILES slang/*.cpp)
add_executable(slang ${SRC_FILES})
set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
set(CMAKE_C_FLAGS_INIT "-Wall -std=c99")
set(CMAKE_C_FLAGS_DEBUG_INIT "-g")
set(CMAKE_C_FLAGS_MINSIZEREL_INIT "-Os -DNDEBUG")
set(CMAKE_C_FLAGS_RELEASE_INIT "-O3 -DNDEBUG")
set(CMAKE_C_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

set(CMAKE_CXX_FLAGS_INIT "-Wall")
set(CMAKE_CXX_FLAGS_DEBUG_INIT "-g")
set(CMAKE_CXX_FLAGS_MINSIZEREL_INIT "-Os -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE_INIT "-O3 -DNDEBUG")
set(CMAKE_CXX_FLAGS_RELWITHDEBINFO_INIT "-O2 -g")

include(CPack)
