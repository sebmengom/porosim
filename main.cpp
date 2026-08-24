#include "montecarlo.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  if (argc == 3) {
    int gridSize{std::stoi(argv[1])};
    int numberOfTrials{std::stoi(argv[2])};

    montecarlo sim(gridSize, numberOfTrials);
    sim.trials();
    sim.printResults();

    return 0;
  } else {
    std::cout << "RUN BY: ./'executable' #gridSize INT #numberOfTrials INT"
              << '\n';
  }
}
