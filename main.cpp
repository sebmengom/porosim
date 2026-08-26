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
    sim.trials();
    auto endTest = std::chrono::steady_clock::now();
    auto elapsedTest1 = std::chrono::duration_cast<std::chrono::milliseconds>(
        endTest - startTest);
    sim.printResults();
    startTest = std::chrono::steady_clock::now();
    sim.newTrials();
    endTest = std::chrono::steady_clock::now();
    auto elapsedTest2 = std::chrono::duration_cast<std::chrono::milliseconds>(
        endTest - startTest);
    sim.printNewResults();
    std::cout << "First Trial: " << elapsedTest1.count() << '\n'
              << "Second Trial: " << elapsedTest2.count() << '\n';

    return 0;
  } else {
    std::cout << "RUN BY: ./'executable' #gridSize INT #numberOfTrials INT"
              << '\n';
  }
}
