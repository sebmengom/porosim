#include "percolator/percolator.h"
#include <cassert>
#include <vector>

percolator::percolator(int n)
    : n(n), top(n * n), bottom((n * n) + 1), arr((n * n) + 2),
      arrTop((n * n) + 1), injectionArr(n * n + 2), gateStatus(n * n, 0),
      finder(n, gateStatus) {
  assert(n > 0);
};

void percolator::openGate(int row, int col) {
  assert(row >= 0 && row < n && col >= 0 && col < n);
  int i{row * n + col};
  int nb{};
  gateStatus[i] = 1;
  if (row == 0) {
    arr.unionSets(i, top);
    arrTop.unionSets(i, top);
  }
  if (row != 0) {
    nb = i - n;
    unionAllThree(i, nb);
  }
  if (row == n - 1) {
    arr.unionSets(i, bottom);
    injectionArr.unionSets(i, bottom);
  }

  if (row != n - 1) {
    nb = i + n;
    unionAllThree(i, nb);
  }

  if (col != 0) {
    nb = i - 1;
    unionAllThree(i, nb);
  }
  if (col != n - 1) {
    nb = i + 1;
    unionAllThree(i, nb);
  }
}

bool percolator::isOpen(int row, int col) {
  assert(row >= 0 && row < n && col >= 0 && col < n);
  int i{row * n + col};
  return gateStatus[i] == 1;
}

bool percolator::percolates() { return arr.connected(top, bottom); }

bool percolator::isFull(int row, int col) {
  assert(row >= 0 && row < n && col >= 0 && col < n);
  return arrTop.connected(top, (row * n + col));
}

bool percolator::injectionReaches() {
  return injectionArr.connected(0, (bottom));
}

void percolator::unionAllThree(int i, int nb) {
  if (gateStatus[nb] == 1) {
    arr.unionSets(i, nb);
    arrTop.unionSets(i, nb);
    injectionArr.unionSets(i, nb);
  };
}

void percolator::runDfsFromInjection() { finder.runDfsFromInjectionPoint(); }

std::vector<int> percolator::findPath(int row, int col) {
  return finder.findPath(row, col);
}
