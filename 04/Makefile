CC=g++
FLAGS=-std=c++17 -Wall
all: test

test: test_proc    
	./test

test_proc: test.o bigint.o
	$(CC) $(FLAGS) -o test test.o bigint.o

test.o: test.cpp bigint.h
	$(CC) $(FLAGS) -c test.cpp

bigint.o: bigint.cpp bigint.h
	$(CC) $(FLAGS) -c bigint.cpp

clean:
	rm -rf *.o test
