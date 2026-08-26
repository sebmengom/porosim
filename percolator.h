#ifndef PERCOLATOR_H
#define PERCOLATOR_H

#include "dsu.h"
#include <vector>

class percolator {
private:
  int n{};
  int top{};
  int bottom{};
  unionFind arr;
  std::vector<int> gateStatus;

public:
  percolator(int n);

  void openGate(int row, int col);

  bool isOpen(int row, int col);

  bool percolates();
};

#endif // !PERCOLATOR_H
