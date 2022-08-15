set(SOURCE_FILE main.cpp)
# add the files for creating executable
add_executable(slangLLVM ${SOURCE_FILE})


#link the libs 
target_link_libraries(slangLLVM 
PRIVATE 
    ast
    frontend
)

#lets use ankels to have cleaner imports 
# Needs to import and pass path to compiler 
# target_include_directories(slangLLVM
# PRIVATE
#     "../ast"
# )
# this is good not good enough
# we provide it from include dir when lib is used
