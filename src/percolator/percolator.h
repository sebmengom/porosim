#ifndef PERCOLATOR_H
#define PERCOLATOR_H

#include "algorithms/dsu.h"
#include "algorithms/pathfinder.h"
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
  pathfinder finder;

public:
  percolator(int n);

  void openGate(int row, int col);

  bool isOpen(int row, int col);

  bool percolates();

  bool isFull(int row, int col);

  bool injectionReaches();

  void unionAllThree(int i, int nb);
  void runDfsFromInjection(int row, int col);
  void runBfsFromInjection(int row, int col);
  std::vector<int> findPath(int row, int col);
};

#endif // !PERCOLATOR_H
