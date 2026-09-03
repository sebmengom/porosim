main: dsu.o percolator.o montecarlo.o pathwriter.o main.o 
	g++ dsu.o percolator.o montecarlo.o pathwriter.o main.o -o main

test: percolator.o testing.o dsu.o 
	g++ percolator.o testing.o dsu.o -o test

dsu.o: dsu.cpp dsu.h
	g++ -std=c++17 -O2 -Wall -Wextra -c dsu.cpp

percolator.o: percolator.cpp percolator.h dsu.h 
	g++ -std=c++17 -O2 -Wall -Wextra -c percolator.cpp

pathwriter.o: pathwriter.cpp pathwriter.h
	g++ -std=c++17 -O2 -Wall -Wextra -c pathwriter.cpp

montecarlo.o : montecarlo.cpp montecarlo.h percolator.h pathwriter.h
	g++ -std=c++17 -O2 -Wall -Wextra -c montecarlo.cpp

testing.o : testing.cpp  percolator.h dsu.h  
	g++ -std=c++17 -O2 -Wall -Wextra -c testing.cpp

main.o : main.cpp montecarlo.h 
	g++ -std=c++17 -O2 -Wall -Wextra -c main.cpp
