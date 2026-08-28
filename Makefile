main: dsu.o percolator.o montecarlo.o main.o 
	g++ dsu.o percolator.o montecarlo.o main.o -o main

dsu.o: dsu.cpp dsu.h
	g++ -std=c++17 -O2 -Wall -Wextra -c dsu.cpp

percolator.o: percolator.cpp percolator.h dsu.h 
	g++ -std=c++17 -O2 -Wall -Wextra -c percolator.cpp

montecarlo.o : montecarlo.cpp montecarlo.h percolator.h
	g++ -std=c++17 -O2 -Wall -Wextra -c montecarlo.cpp

main.o : main.cpp montecarlo.h 
	g++ -std=c++17 -O2 -Wall -Wextra -c main.cpp


