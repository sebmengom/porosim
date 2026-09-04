#ifndef PERCOLATOR_H
#define PERCOLATOR_H

#include "algorithms/dsu.h"
#include <stack>
#include <vector>
class percolator {
private:
  int n{};
  int top{};
  int bottom{};
  unionFind arr;
  unionFind arrTop;
  unionFind injectionArr;
  std::vector<int> gateStatus;
  std::vector<int> visited;
  std::vector<int> parent;
  void resetVisited();
  void pushToStack(int nb, int parentIndex, std::stack<int> &stack,
                   std::vector<int> &parentArray);

public:
  percolator(int n);

  void openGate(int row, int col);

  bool isOpen(int row, int col);

  bool percolates();

  bool isFull(int row, int col);

  void depthFirstSearch();

  void runDFS();

  bool isVisited(int row, int col);

  std::vector<int> findPath(int row, int col);

  bool injectionReaches(int row, int col);
};

#endif // !PERCOLATOR_H
