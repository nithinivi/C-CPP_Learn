set(SOURCE_FILES Visitor.cpp Expression.cpp)
add_library(ast ${SOURCE_FILES})

target_link_libraries(ast 
PUBLIC 
    contexts
PRIVATE
    frontend
)

    
# get the include dirs 
target_include_directories(ast 
INTERFACE  
    .
PUBLIC
    ${PROJECT_SOURCE_DIR}/meta 
)

# INTERFACE tells to use includes to other libs but on the ast