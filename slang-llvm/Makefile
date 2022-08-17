
all: 
	cmake -S . -B build
	$(MAKE) -C build 

dep:
	cd build && cmake .. --graphviz=graph.dot && dot -Tpng graph.dot -o graphImage.png 
 
clean:
	rm -rf build 
	mkdir build

cc: clean all
