#include "percolator.h"
#include <cassert>
#include <vector>

percolator::percolator(int n)
    : n(n), top(n * n), bottom((n * n) + 1), arr((n * n) + 2),
      arrTop((n * n) + 1), gateStatus(n * n, 0), visited(n * n, 0) {};
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
    if (gateStatus[nb] == 1) {
      arr.unionSets(i, nb);
      arrTop.unionSets(i, nb);
    };
  }
  if (row == n - 1) {
    arr.unionSets(i, bottom);
  }

  if (row != n - 1) {
    nb = i + n;
    if (gateStatus[nb] == 1) {
      arr.unionSets(i, nb);
      arrTop.unionSets(i, nb);
    }
  }

  if (col != n - 1) {
    nb = i + 1;
    if (gateStatus[nb] == 1) {
      arr.unionSets(i, nb);
      arrTop.unionSets(i, nb);
    };
  }

  if (col != 0) {
    nb = i - 1;
    if (gateStatus[nb] == 1) {
      arr.unionSets(i, nb);
      arrTop.unionSets(i, nb);
    }
  }
}

bool percolator::isOpen(int row, int col) {
  int i{row * n + col};
  return gateStatus[i] == 1;
}

bool percolator::percolates() { return arr.connected(top, bottom); }

bool percolator::isFull(int row, int col) {
  return arrTop.connected(top, (row * n + col));
}

void percolator::depthFirstSearch(int row, int col) {

  int i{row * n + col};

  if (visited[i] == 1) {
    return;
  }

  if (isOpen(row, col)) {
    visited[i] = 1;
  } else {
    return;
  }
  if (col != n - 1) {
    depthFirstSearch(row, col + 1);
  }
  if (row != 0) {
    depthFirstSearch(row - 1, col);
  }
  if (col != 0) {
    depthFirstSearch(row, col - 1);
  }

  if (row != n - 1) {
    depthFirstSearch(row + 1, col);
  }
}

void percolator::resetVisited() {
  for (auto &i : visited) {
    i = 0;
  }
}

void percolator::runDFS(int row, int col) {
  percolator::resetVisited();
  percolator::depthFirstSearch(row, col);
}

bool percolator::isVisited(int row, int col) {
  return 1 == visited[row * n + col];
}
