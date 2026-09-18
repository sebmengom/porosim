#include "simulation/montecarlo.h"
#include "percolator/percolator.h"
#include "utils/pathwriter.h"
#include <algorithm>
#include <cassert>
#include <chrono>
#include <iostream>
#include <numeric>
#include <vector>

montecarlo::montecarlo(int gridSize, int numberOfTrials)
    : gridSize(gridSize), numberOfTrials(numberOfTrials) {};

void montecarlo::trials() {
  results.clear();
  for (int i = 0; i < numberOfTrials; i++) {
    results.push_back(ultimateSingleTrial(0));
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
        auto start = std::chrono::steady_clock::now();
        int dfsExit{pGrid.runDfsFromInjection()};
        auto end = std::chrono::steady_clock::now();
        auto elapsedDfs =
            std::chrono::duration<double, std::milli>(end - start).count();
        dfsTimes.push_back(elapsedDfs);
        int dfsRow{dfsExit / gridSize};
        int dfsCol{dfsExit % gridSize};
        path = pGrid.findPath(dfsRow, dfsCol);
        int writeStatus =
            writePathToCsv(path, gridSize, filename(trialNum) + "_dfs");
        assert(writeStatus == 0);

        start = std::chrono::steady_clock::now();
        int bfsExit{pGrid.runBfsFromInjection()};
        end = std::chrono::steady_clock::now();

        auto elapsedBfs =
            std::chrono::duration<double, std::milli>(end - start).count();

        bfsTimes.push_back(elapsedBfs);

        int bfsRow{bfsExit / gridSize};
        int bfsCol{bfsExit % gridSize};
        path = pGrid.findPath(bfsRow, bfsCol);

        writeStatus =
            writePathToCsv(path, gridSize, filename(trialNum) + "_bfs");
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
void montecarlo::printResults(std::vector<double> resultsList) {
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
const std::vector<double> &montecarlo::getResults() const { return results; }
const std::vector<double> &montecarlo::getInjectionResults() const {
  return injectionResults;
}
const std::vector<double> &montecarlo::getDfsTimes() const { return dfsTimes; }
const std::vector<double> &montecarlo::getBfsTimes() const { return bfsTimes; }
