set(SOURCE_FILES Visitor.cpp)
add_library(ast ${SOURCE_FILES})

add_subdirectory(expression)


target_link_libraries(ast 
PUBLIC 
    meta
    contexts
    LLVMSupport
    expression
PRIVATE
    frontend
)

    
# get the include dirs 
target_include_directories(ast 
INTERFACE  
    .
PUBLIC
    ${LLVM_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/meta 
    ${PROJECT_SOURCE_DIR}/ast/expression
    
)
