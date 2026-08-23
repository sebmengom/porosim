#include "dsu.h"
#include "percolator.h"
#include <iostream>

int main() {
  percolator p{4};
  p.openGate(0, 3);
  p.openGate(1, 2);
  p.openGate(0, 2);
  p.openGate(2, 1);
  p.openGate(2, 2);
  p.openGate(3, 2);

  std::cout << p.percolates();
}
