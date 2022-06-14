all: hello removeo

hello: main.o compiler.o machine.o
	g++ main.o compiler.o machine.o -o bfvm

compiler.o: compiler.cpp
	g++ -c compiler.cpp

machine.o: machine.cpp 
	g++ -c machine.cpp 

main.o: main.cpp 
	g++ -c main.cpp 

removeo :
	rm -rf *.o

clean: removeo
	rm bfvm
