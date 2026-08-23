#include "dsu.h"
#include <utility>

unionFind::unionFind(int n) {
  parent.resize(n);
  size.assign(n, 1);

  for (int i = 0; i < n; i++) {
    parent[i] = i;
  }
}

void unionFind::unionSets(int a, int b) {
  a = findSet(a);
  b = findSet(b);

  if (a != b) {
    if (size[a] < size[b]) {
      std::swap(a, b);
    }
    parent[b] = a;
    size[a] += size[b];
  };
}
int unionFind::findSet(int x) {
  if (x == parent[x]) {
    return x;
  }

  return parent[x] = findSet(parent[x]);
}
bool unionFind::connected(int a, int b) { return findSet(a) == findSet(b); }
