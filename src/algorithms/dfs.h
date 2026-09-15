#ifndef DFS_H
#define DFS_H
#include <stack>
#include <vector>
class pathfinder {
private:
  int n{};
  const std::vector<int> &gateStatus;
  std::vector<int> visited;
  std::vector<int> parent;
  void resetVisited();
  void pushToStack(int nb, int parentIndex, std::stack<int> &stack,
                   std::vector<int> &parentArray);
  void depthFirstSearch();

  bool isVisited(int row, int col);

public:
  pathfinder(int n, const std::vector<int> &gateStatus);
  void runDfsFromInjectionPoint();
  std::vector<int> findPath(int row, int col);
};

#endif // !DFS_H
