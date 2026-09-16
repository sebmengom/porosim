#include "algorithms/pathfinder.h"
#include <cassert>
#include <stack>
pathfinder::pathfinder(int n, const std::vector<int> &gateStatus)
    : n(n), gateStatus(gateStatus), visited(n * n, 0), parent(n * n, 0) {};
void pathfinder::depthFirstSearch() {

  std::stack<int> stack{};
  visited[0] = 1;
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
void pathfinder::resetVisited() {
  for (auto &i : visited) {
    i = 0;
  }
  for (auto &i : parent) {
    i = 0;
  }
}

void pathfinder::runDfsFromInjectionPoint() {
  pathfinder::resetVisited();
  pathfinder::depthFirstSearch();
}

bool pathfinder::isVisited(int row, int col) {
  assert(row >= 0 && row < n && col >= 0 && col < n);
  return 1 == visited[row * n + col];
}

void pathfinder::pushToStack(int nb, int parentIndex, std::stack<int> &stack,
                             std::vector<int> &parentArray) {
  visited[nb] = 1;
  parentArray[nb] = parentIndex;
  stack.push(nb);
}

std::vector<int> pathfinder::findPath(int row, int col) {
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
