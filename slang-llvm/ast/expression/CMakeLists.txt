set(SOURCE_FILES Expression.cpp NumericExpression.cpp)
add_library(expression ${SOURCE_FILES})


target_link_libraries(expression
PUBLIC
    ast
)
    
# get the include dirs 
target_include_directories(expression 
INTERFACE  
    .
PUBLIC 
    ${LLVM_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/contexts
    ${PROJECT_SOURCE_DIR}/ast 
    ${PROJECT_SOURCE_DIR}/meta

)

# INTERFACE tells to use includes to other libs but on the ast