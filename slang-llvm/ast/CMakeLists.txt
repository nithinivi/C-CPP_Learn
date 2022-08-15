set(SOURCE_FILES Visitor.cpp Expression.cpp)
add_library(ast ${SOURCE_FILES})

target_include_directories(ast PUBLIC .
    "${PROJECT_SOURCE_DIR}/contexts"
    "${PROJECT_SOURCE_DIR}/meta"
)