CC = g++ 
CFLAGS=-I -Wall 

TARGET = my_visitor

all: payload.o  server.o wire.o
	$(CC) $(CFLAGS) -pthread payload.o server.o  -o server.out
	$(CC) $(CFLAGS) -pthread payload.o wire.o  -o wire.out
	$(RM) count *.o
	
wire.o:  wire.cpp 
	$(CC) $(CFLAGS) -c wire.cpp

server.o: server.cpp server.hpp
	$(CC) $(CFLAGS) -c server.cpp

payload.o: payload.cpp payload.hpp
	$(CC) $(CFLAGS) -c payload.cpp

clean: 
	$(RM) count *.o *.out