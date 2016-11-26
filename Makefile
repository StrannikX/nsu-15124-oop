all: main

run: all
	./main

clean:
	rm *.o
	rm main

main: main.o expr_parser.o Expressions.o
	g++ main.o expr_parser.o Expressions.o -std=gnu++14 -lstdc++ -o main

main.o: main.cpp Expressions.hpp
	g++ main.cpp -c -std=gnu++14 -O2 -o main.o

expr_parser.o: expr_parser.cpp expr_parser.hpp Expressions.hpp
	g++ expr_parser.cpp -c -std=gnu++14 -O2 -o expr_parser.o

Expressions.o: Expressions.hpp Expressions.cpp
	g++ Expressions.cpp -c -std=gnu++14 -O2 -o Expressions.o
