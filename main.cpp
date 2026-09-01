#include "montecarlo.h"
#include <chrono>
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  if (argc == 3) {
    int gridSize{std::stoi(argv[1])};
    int numberOfTrials{std::stoi(argv[2])};

    montecarlo sim(gridSize, numberOfTrials);
    auto startTest = std::chrono::steady_clock::now();
    sim.newTrials();
    auto endTest = std::chrono::steady_clock::now();
    auto elapsedTest = std::chrono::duration_cast<std::chrono::milliseconds>(
        endTest - startTest);
    sim.printNewResults(sim.newResults);
    std::cout << "Time elapsed: " << elapsedTest.count() << '\n';

    montecarlo injectionSim(gridSize, numberOfTrials);
    startTest = std::chrono::steady_clock::now();
    injectionSim.injectionTrials();
    endTest = std::chrono::steady_clock::now();

    elapsedTest = std::chrono::duration_cast<std::chrono::milliseconds>(
        endTest - startTest);

    sim.printNewResults(injectionSim.injectionResults);
    std::cout << "Time elapsed: " << elapsedTest.count() << '\n';

    return 0;
  } else {
    std::cout << "RUN BY: ./'executable' #gridSize INT #numberOfTrials INT"
              << '\n';
  }
}
