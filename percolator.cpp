#include "percolator.h"

percolator::percolator(int n)
    : n(n), arr(n * n + 2), gateStatus(n * n, 0), top(n * n),
      bottom((n * n) + 1) {};
void percolator::openGate(int row, int col) {
  int i{row * n + col};
  int nb{};
  gateStatus[i] = 1;
  if (row == 0) {
    arr.unionSets(i, top);
  }
  if (row != 0) {
    nb = i - n;
    if (gateStatus[nb] == 1) {
      arr.unionSets(i, nb);
    };
  }
  if (row == n - 1) {
    arr.unionSets(i, bottom);
  }

  if (row != n - 1) {
    nb = i + n;
    if (gateStatus[nb] == 1) {
      arr.unionSets(i, nb);
    }
  }

  if (col != n - 1) {
    nb = i + 1;
    if (gateStatus[nb] == 1) {
      arr.unionSets(i, nb);
    };
  }

  if (col != 0) {
    nb = i - 1;
    if (gateStatus[nb] == 1) {
      arr.unionSets(i, nb);
    }
  }
}

bool percolator::isOpen(int row, int col) {
  int i{row * n + col};
  return gateStatus[i] == 1;
}

bool percolator::percolates() { return arr.connected(top, bottom); }
