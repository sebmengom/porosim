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
  unionFind arrTop;
  std::vector<int> gateStatus;

public:
  percolator(int n);

  void openGate(int row, int col);

  bool isOpen(int row, int col);

  bool percolates();

  bool isFull(int row, int col);
};

#endif // !PERCOLATOR_H
