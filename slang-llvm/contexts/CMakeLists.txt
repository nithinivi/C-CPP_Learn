
set(SOURCE_FILES Symbol.cpp)

add_library(contexts ${SOURCE_FILES})

target_include_directories(contexts PUBLIC .
    "${PROJECT_SOURCE_DIR}/meta"
)
