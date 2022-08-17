set(SOURCE_FILES Visitor.cpp)
add_library(ast ${SOURCE_FILES})

target_link_libraries(ast 
PUBLIC 
    contexts
    LLVMSupport
PRIVATE
    meta
    expression
    frontend
)

    
# get the include dirs 
target_include_directories(ast 
INTERFACE  
    .
PUBLIC
    ${PROJECT_SOURCE_DIR}/meta 
    ${PROJECT_SOURCE_DIR}/ast/expression
    ${LLVM_INCLUDE_DIRS}

)


add_subdirectory(expression)

# INTERFACE tells to use includes to other libs but on the ast