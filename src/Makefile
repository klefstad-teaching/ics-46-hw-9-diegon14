CXXFLAGS=-ggdb -std=c++20 -Wall -Werror -Wfatal-errors -pedantic

all: ladder_main

ladder_main: ladder_main.cpp ladder.o 
	g++ $(CXXFLAGS) ladder_main.cpp ladder.o -o main

ladder.o: ladder.cpp ladder.h 
	g++ $(CXXFLAGS) -c ladder.cpp -o ladder.o

clean:
	rm -qs *.o