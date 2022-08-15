set(SOURCE_FILES Expression.cpp)

add_library(expr STATIC ${SOURCE_FILES})

target_include_directories(expr INTERFACE .)
