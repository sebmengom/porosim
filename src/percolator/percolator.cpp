#include "percolator/percolator.h"
#include <cassert>
#include <stack>
#include <vector>

percolator::percolator(int n)
    : n(n), top(n * n), bottom((n * n) + 1), arr((n * n) + 2),
      arrTop((n * n) + 1), injectionArr(n * n + 2), gateStatus(n * n, 0),
      visited(n * n, 0), parent(n * n, 0) {
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
    if (gateStatus[nb] == 1) {
      arr.unionSets(i, nb);
      arrTop.unionSets(i, nb);
      injectionArr.unionSets(i, nb);
    };
  }
  if (row == n - 1) {
    arr.unionSets(i, bottom);
    injectionArr.unionSets(i, bottom);
  }

  if (row != n - 1) {
    nb = i + n;
    if (gateStatus[nb] == 1) {
      arr.unionSets(i, nb);
      arrTop.unionSets(i, nb);
      injectionArr.unionSets(i, nb);
    }
  }

  if (col != n - 1) {
    nb = i + 1;
    if (gateStatus[nb] == 1) {
      arr.unionSets(i, nb);
      arrTop.unionSets(i, nb);
      injectionArr.unionSets(i, nb);
    };
  }

  if (col != 0) {
    nb = i - 1;
    if (gateStatus[nb] == 1) {
      arr.unionSets(i, nb);
      arrTop.unionSets(i, nb);
      injectionArr.unionSets(i, nb);
    }
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

void percolator::depthFirstSearch() {

  std::stack<int> stack{};
  visited[0] = 1;
  openGate(0, 0);
  parent[0] = -1;
  stack.push(0);

  while (!(stack.empty())) {
    int i{stack.top()};
    stack.pop();
    int nb{};
    int row{i / n};
    int col{i % n};

    if (row != 0) {
      nb = i - n;

      if (gateStatus[nb] == 1 && visited[nb] == 0) {
        pushToStack(nb, i, stack, parent);
      }
    }

    if (row != n - 1) {
      nb = i + n;
      if (gateStatus[nb] == 1 && visited[nb] == 0) {
        pushToStack(nb, i, stack, parent);
      }
    }

    if (col != n - 1) {
      nb = i + 1;

      if (gateStatus[nb] == 1 && visited[nb] == 0) {
        pushToStack(nb, i, stack, parent);
      }
    }

    if (col != 0) {
      nb = i - 1;
      if (gateStatus[nb] == 1 && visited[nb] == 0) {
        pushToStack(nb, i, stack, parent);
      }
    }
  }
}

void percolator::resetVisited() {
  for (auto &i : visited) {
    i = 0;
  }
  for (auto &i : parent) {
    i = 0;
  }
}

void percolator::runDFS() {
  percolator::resetVisited();
  percolator::depthFirstSearch();
}

bool percolator::isVisited(int row, int col) {
  assert(row >= 0 && row < n && col >= 0 && col < n);
  return 1 == visited[row * n + col];
}

void percolator::pushToStack(int nb, int parentIndex, std::stack<int> &stack,
                             std::vector<int> &parentArray) {
  visited[nb] = 1;
  parentArray[nb] = parentIndex;
  stack.push(nb);
}
std::vector<int> percolator::findPath(int row, int col) {
  assert(isVisited(row, col));
  int i{row * n + col};
  std::vector<int> path{};
  int parentIndex{i};
  while (parentIndex != -1) {
    path.push_back(parentIndex);
    parentIndex = parent[parentIndex];
  }
  return path;
}

bool percolator::injectionReaches(int row, int col) {
  assert(isOpen(0, 0));
  assert(row >= 0 && row < n && col >= 0 && col < n);
  return injectionArr.connected(0, (bottom));
}
