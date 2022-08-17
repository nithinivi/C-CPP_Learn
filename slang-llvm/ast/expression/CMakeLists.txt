set(SOURCE_FILES Expression.cpp NumericExpression.cpp)
add_library(experssion ${SOURCE_FILES})


target_link_libraries(experssion
PRIVATE
    ast
    meta
    contexts
    LLVMSupport 
)

    
# get the include dirs 
target_include_directories(experssion 
INTERFACE  
    .
PUBLIC 
    ${LLVM_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/ast 
    ${PROJECT_SOURCE_DIR}/meta
    ${PROJECT_SOURCE_DIR}/contexts
)

# INTERFACE tells to use includes to other libs but on the ast