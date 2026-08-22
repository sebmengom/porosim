#ifndef PERCOLATOR_H
#define PERCOLATOR_H

#include "dsu.h"
#include <vector>

class percolator {
public:
  percolator(int n);
  unionFind arr{(percolator::n * percolator::n) + 2};
  std::vector<int> gateStatus =
      std::vector<int>(percolator::n * percolator::n, 0);

  void openGate(int row, int col);

  int isOpen(int row, int col);

  bool percolates();

private:
  int n{};
  int top{};
  int bottom{};
};

#endif // !PERCOLATOR_H
