CC=g++
FLAGS=-std=c++17 -Wall
all: test

test: test_proc    
	./test

test_proc: test.o matrix.o
	$(CC) $(FLAGS) -o test test.o matrix.o

test.o: test.cpp matrix.h
	$(CC) $(FLAGS) -c test.cpp

matrix.o: matrix.cpp matrix.h
	$(CC) $(FLAGS) -c matrix.cpp

clean:
	rm -rf *.o test
