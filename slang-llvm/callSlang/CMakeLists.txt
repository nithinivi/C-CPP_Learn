set(SOURCE_FILE main.cpp)
# add the files for creating executable
add_executable(slangLLVM ${SOURCE_FILE})


#link the libs 
target_link_libraries(slangLLVM 
PRIVATE
    ast
    frontend
)
