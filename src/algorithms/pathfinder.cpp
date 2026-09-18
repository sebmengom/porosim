#include "algorithms/pathfinder.h"
#include "percolator/percolator.h"
#include <cassert>
#include <filesystem>
#include <queue>
#include <stack>
#include <vector>
pathfinder::pathfinder(int n, const std::vector<int> &gateStatus)
    : n(n), gateStatus(gateStatus), visited(n * n, 0), parent(n * n, 0) {};
int pathfinder::depthFirstSearch() {

  std::stack<int> stack{};
  visited[0] = 1;
  parent[0] = -1;
  stack.push(0);

  while (!(stack.empty())) {
    int i{stack.top()};
    stack.pop();
    if (i / n == n - 1) {
      return i;
    }

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
  assert(false &&
         "no debería pasar, injectionReaches ya confirmó que hay camino");
  ;
  return -1;
}
void pathfinder::resetVisited() {
  for (auto &i : visited) {
    i = 0;
  }
  for (auto &i : parent) {
    i = 0;
  }
}

int pathfinder::runDfsFromInjectionPoint() {
  pathfinder::resetVisited();
  return pathfinder::depthFirstSearch();
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

int pathfinder::breadthFirstSearch() {
  std::queue<int> queue{};
  visited[0] = 1;
  parent[0] = -1;
  queue.push(0);

  while (queue.size() != 0) {
    int i{queue.front()};
    queue.pop();
    if (i / n == n - 1) {
      return i;
    }
    int nb{};
    int row{i / n};
    int col{i % n};

    if (row != 0) {
      nb = i - n;

      if (gateStatus[nb] == 1 && visited[nb] == 0) {
        pushToQueue(nb, i, queue, parent);
      }
    }

    if (row != n - 1) {
      nb = i + n;
      if (gateStatus[nb] == 1 && visited[nb] == 0) {
        pushToQueue(nb, i, queue, parent);
      }
    }

    if (col != n - 1) {
      nb = i + 1;

      if (gateStatus[nb] == 1 && visited[nb] == 0) {
        pushToQueue(nb, i, queue, parent);
      }
    }

    if (col != 0) {
      nb = i - 1;
      if (gateStatus[nb] == 1 && visited[nb] == 0) {
        pushToQueue(nb, i, queue, parent);
      }
    }
  }
  assert(false &&
         "no debería pasar, injectionReaches ya confirmó que hay camino");
  return -1;
}

void pathfinder::pushToQueue(int nb, int parentIndex, std::queue<int> &queue,
                             std::vector<int> &parentArray) {
  visited[nb] = 1;
  parentArray[nb] = parentIndex;
  queue.push(nb);
}

int pathfinder::runBfsFromInjectionPoint() {
  pathfinder::resetVisited();
  return pathfinder::breadthFirstSearch();
}
