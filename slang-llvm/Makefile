
all: 
	cmake -S . -B build -G Ninja
	cmake --build build


dep:
	cd build && cmake .. --graphviz=graph.dot && dot -Tpng graph.dot -o graphImage.png 
 
clean:
	rm -rf build 
	mkdir build

cc: clean all
