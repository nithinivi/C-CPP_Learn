cmake_minimum_required(VERSION 3.0.0)
project(slang-step-5 VERSION 0.1.0)

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
include(CPack)
