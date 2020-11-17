CC=g++
FLAGS=-std=c++17 -Wall
all: test

test: test_proc    
	./test

test_proc: test.o
	$(CC) $(FLAGS) -o test test.o

test.o: test.cpp
	$(CC) $(FLAGS) -c test.cpp

clean:
	rm -rf *.o test
