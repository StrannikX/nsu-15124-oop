all: list

run: list
	./list

clean:
	rm *.o
	rm list

list: main.o
	g++ main.o -std=gnu++0x -lstdc++ -o list

main.o: main.cpp List.h
	g++ main.cpp -c -std=gnu++0x -O2 -o main.o
