
set(SOURCE_FILES Parser.cpp)

add_library(frontend STATIC ${SOURCE_FILES})

target_link_libraries(frontend 
PRIVATE 
    ast 
    contexts
    meta
)

# get the include dirs 
target_include_directories(frontend 
INTERFACE 
    .
PRIVATE
    "${PROJECT_SOURCE_DIR}/ast/expression"
)