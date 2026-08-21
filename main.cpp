#include "dsu.h"
#include <iostream>

int main() {
  unionFind arr(10);
  arr.unionSets(4, 1);
  std::cout << arr.findSet(1);
  return 0;
}
