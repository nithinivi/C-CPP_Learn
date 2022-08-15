
set(SOURCE_FILES Symbol.cpp)

add_library(contexts ${SOURCE_FILES})


# get the include dirs 
target_include_directories(contexts INTERFACE .)