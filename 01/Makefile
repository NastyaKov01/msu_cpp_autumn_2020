CC=g++
FLAGS=-std=c++17 -Wall
all: test

test: test_proc    
	./test

test_proc: test.o allocator.o
	$(CC) $(FLAGS) -o test test.o allocator.o

test.o: test.cpp allocator.h
	$(CC) $(FLAGS) -c test.cpp

allocator.o: allocator.cpp allocator.h
	$(CC) $(FLAGS) -c allocator.cpp

clean:
	rm -rf *.o test
