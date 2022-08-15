set(SOURCE_FILES Visitor.cpp)
add_library(ast STATIC ${SOURCE_FILES})

# target_link_libraries(AST PUBLIC EXPR)
target_include_directories(ast INTERFACE .)