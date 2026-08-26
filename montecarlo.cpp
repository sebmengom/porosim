#include "montecarlo.h"
#include "percolator.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>
montecarlo::montecarlo(int gridSize, int numberOfTrials)
    : gridSize(gridSize), numberOfTrials(numberOfTrials) {};

void montecarlo::trials() {
  for (double pItem : p) {
    int percolated{};
    for (int i{0}; i < numberOfTrials; i++) {

      bool result = singleTrial(pItem);
      if (result) {
        percolated++;
      };
    };
    results.push_back(
        {pItem, static_cast<double>(percolated) / numberOfTrials});
  }
};

bool montecarlo::singleTrial(double p) {
  percolator pGrid{gridSize};
  int row{};
  int col{};
  double dist{};
  for (int i{0}; i < gridSize * gridSize; i++) {
    row = i / gridSize;
    col = i % gridSize;
    dist = distribution(machine);
    if (dist < p) {
      pGrid.openGate(row, col);
    }
  }
  return pGrid.percolates();
}
void montecarlo::printResults() {
  for (const auto &r : results) {
    std::cout << r.first << ',' << r.second << '\n';
  }
}

void montecarlo::newTrials() {
  for (int i = 0; i < numberOfTrials; i++) {
    newResults.push_back(newSingleTrial());
  };
}

double montecarlo::newSingleTrial() {
  percolator pGrid{gridSize};
  int row{};
  int col{};
  std::vector<int> shuffled(gridSize * gridSize);
  std::iota(shuffled.begin(), shuffled.end(), 0);
  std::shuffle(shuffled.begin(), shuffled.end(), machine);
  for (int i = 0; i < gridSize * gridSize - 1; i++) {
    row = shuffled[i] / gridSize;
    col = shuffled[i] % gridSize;
    pGrid.openGate(row, col);
    if (pGrid.percolates()) {
      return (static_cast<double>(i) + 1) / (gridSize * gridSize);
    }
  }
  return 1;
}

void montecarlo::printNewResults() {
  double result{};
  for (double r : newResults) {
    result += r;
  }
  std::cout << "Threshold: " << result / numberOfTrials << '\n';
}
