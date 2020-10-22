CC=g++
FLAGS=-std=c++17 -Wall
all: test

test: test_proc    
	./test

test_proc: test.o parser.o
	$(CC) $(FLAGS) -o test test.o parser.o

test.o: test.cpp parser.h
	$(CC) $(FLAGS) -c test.cpp

parser.o: parser.cpp parser.h
	$(CC) $(FLAGS) -c parser.cpp

clean:
	rm -rf *.o test
