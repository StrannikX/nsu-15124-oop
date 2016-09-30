all: string

string: main.o string.o
	g++ -lstdc++ string.o main.o -o string

main.o: main.cpp

string.o: String.cpp String.h
	g++ -c String.cpp -o string.o
