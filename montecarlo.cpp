#include "montecarlo.h"
#include "percolator.h"
#include <iostream>
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
