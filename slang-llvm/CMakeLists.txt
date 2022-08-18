cmake_minimum_required(VERSION 3.16.3)

# set the project name
# https://stackoverflow.com/questions/71740678/cmake-error-in-findterminfo-with-clang-15-on-macos
project(slangLLvm VERSION 1.0 LANGUAGES C CXX)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_BUILD_TYPE "Debug")


set(LLVM_DIR /usr/lib/llvm-14/lib/cmake/llvm)

find_package(LLVM REQUIRED CONFIG
             PATHS ${search_paths}
             NO_DEFAULT_PATH)


# https://llvm.org/docs/CMake.html#embedding-llvm-in-your-project

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")


include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
add_definitions(${LLVM_DEFINITIONS_LIST})

add_subdirectory(meta)
add_subdirectory(contexts)
add_subdirectory(ast)
add_subdirectory(frontend)
add_subdirectory(callSlang)

