
set(SOURCE_FILES parser.cpp)

add_library(frontend STATIC ${SOURCE_FILES})

target_include_directories(frontend INTERFACE .)
