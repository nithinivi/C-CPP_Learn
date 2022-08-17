
all: prepare
	cmake -S . -B build
	$(MAKE) -C build

dep:
	cd build && cmake .. --graphviz=graph.dot && dot -Tpng graph.dot -o graphImage.png 

prepare:
	rm -rf build 
	mkdir build
