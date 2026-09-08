#include "simulation/montecarlo.h"
#include "percolator/percolator.h"
#include "utils/pathwriter.h"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <numeric>
#include <vector>

montecarlo::montecarlo(int gridSize, int numberOfTrials)
    : gridSize(gridSize), numberOfTrials(numberOfTrials) {};

void montecarlo::trials() {
  results.clear();
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

bool montecarlo::singleTrial(double pItem) {
  percolator pGrid{gridSize};
  int row{};
  int col{};
  double dist{};
  for (int i{0}; i < gridSize * gridSize; i++) {
    row = i / gridSize;
    col = i % gridSize;
    dist = distribution(machine);
    if (dist < pItem) {
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
  newResults.clear();
  for (int i = 0; i < numberOfTrials; i++) {
    newResults.push_back(ultimateSingleTrial(0));
  };
}

double montecarlo::ultimateSingleTrial(
    int offset,
    int trialNum) { // Offset being 1 means that there is an injection.
  assert(offset == 0 || offset == 1);
  percolator pGrid{gridSize};
  int row{};
  int col{};
  if (offset == 1) {
    pGrid.openGate(0, 0);
  }
  std::vector<int> shuffled(gridSize * gridSize);
  std::iota(shuffled.begin(), shuffled.end(), 0);
  std::shuffle(shuffled.begin() + offset, shuffled.end(), machine);
  for (int i = offset; i < gridSize * gridSize; i++) {
    row = shuffled[i] / gridSize;
    col = shuffled[i] % gridSize;
    pGrid.openGate(row, col);

    if (offset == 1) {
      if (pGrid.injectionReaches()) {
        pGrid.runDfsFromInjection();
        path = pGrid.findPath(row, col);
        int writeStatus = writePathToCsv(path, gridSize, filename(trialNum));
        assert(writeStatus == 0);
        return (static_cast<double>(i) + 1) / (gridSize * gridSize);
      }
    } else {
      if (pGrid.percolates()) {
        return (static_cast<double>(i) + 1) / (gridSize * gridSize);
      }
    }
  }
  return 1;
}
void montecarlo::printNewResults(std::vector<double> resultsList) {
  double result{};
  for (double r : resultsList) {
    result += r;
  }
  std::cout << "Threshold: " << result / numberOfTrials << '\n';
}

void montecarlo::injectionTrials() {
  injectionResults.clear();
  for (int i = 0; i < numberOfTrials; i++) {
    injectionResults.push_back(ultimateSingleTrial(1, i));
  };
}
const std::vector<double> &montecarlo::getNewResults() const {
  return newResults;
}
const std::vector<double> &montecarlo::getInjectionResults() const {
  return injectionResults;
}
