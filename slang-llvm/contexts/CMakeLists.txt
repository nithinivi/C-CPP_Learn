
set(SOURCE_FILES Symbol.cpp)

add_library(contexts STATIC ${SOURCE_FILES} )

target_include_directories(contexts INTERFACE .)
