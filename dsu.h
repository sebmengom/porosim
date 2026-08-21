#ifndef dsu_h
#define dsu_h

#include <vector>
class unionFind {
public:
  unionFind(int n);
  int findSet(int x);
  void unionSets(int a, int b);

private:
  std::vector<int> parent;
  std::vector<int> size;
};

#endif // dsu_h
