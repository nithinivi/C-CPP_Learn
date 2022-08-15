
set(SOURCE_FILES Parser.cpp)

add_library(frontend STATIC ${SOURCE_FILES})

target_include_directories(frontend INTERFACE
    "${PROJECT_SOURCE_DIR}/meta"
    "${PROJECT_SOURCE_DIR}/ast"
)
