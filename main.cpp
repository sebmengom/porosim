#include "dsu.h"
#include <iostream>

int main() {
  unionFind arr(10);
  arr.unionSets(4, 1);
  arr.unionSets(3, 4);
  arr.unionSets(5, 3);
  arr.unionSets(2, 1);

  std::cout << (arr.findSet(3) == arr.findSet(5)) << '\n'
            << (arr.findSet(9) == arr.findSet(3));
  return 0;
}
