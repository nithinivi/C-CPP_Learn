set(SOURCE_FILE main.cpp)
# add the files for creating executable
add_executable(slangLLVM ${SOURCE_FILE})

llvm_map_components_to_libnames(llvm_libs support core irreader)

#link the libs 
target_link_libraries(slangLLVM 
PUBLIC
    ${llvm_libs}
PRIVATE
    ast
    frontend
)
