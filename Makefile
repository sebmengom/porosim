main: dsu.o percolator.o montecarlo.o pathwriter.o main.o 
	g++ dsu.o percolator.o montecarlo.o pathwriter.o main.o -o main

test: percolator.o testing.o dsu.o 
	g++ percolator.o testing.o dsu.o -o test

dsu.o: src/algorithms/dsu.cpp src/algorithms/dsu.h
	g++ -std=c++17 -O2 -Wall -Wextra -Isrc -c src/algorithms/dsu.cpp

percolator.o: src/percolator/percolator.cpp src/percolator/percolator.h src/algorithms/dsu.h
	g++ -std=c++17 -O2 -Wall -Wextra -Isrc -c src/percolator/percolator.cpp

pathwriter.o: src/utils/pathwriter.cpp src/utils/pathwriter.h
	g++ -std=c++17 -O2 -Wall -Wextra -Isrc -c src/utils/pathwriter.cpp

montecarlo.o : src/simulation/montecarlo.cpp src/simulation/montecarlo.h src/percolator/percolator.h src/utils/pathwriter.h
	g++ -std=c++17 -O2 -Wall -Wextra -Isrc -c src/simulation/montecarlo.cpp

testing.o : tests/testing.cpp  src/percolator/percolator.h src/algorithms/dsu.h
	g++ -std=c++17 -O2 -Wall -Wextra -Isrc -c tests/testing.cpp

main.o : src/main.cpp src/simulation/montecarlo.h
	g++ -std=c++17 -O2 -Wall -Wextra -Isrc -c src/main.cpp
