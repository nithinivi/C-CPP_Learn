
set(SOURCE_FILES Symbol.cpp)

add_library(contexts ${SOURCE_FILES})

target_link_libraries( contexts

PRIVATE
    meta
    LLVMSupport
)

# get the include dirs 
target_include_directories(contexts 
INTERFACE 
    . 
PRIVATE
    ${LLVM_INCLUDE_DIRS}
    ${PROJECT_SOURCE_DIR}/meta
)