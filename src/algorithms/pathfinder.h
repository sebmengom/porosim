#ifndef PATHFINDER_H
#define PATHFINDER_H
#include <queue>
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

  void pushToQueue(int nb, int parentIndex, std::queue<int> &queue,
                   std::vector<int> &parentArray);

  void depthFirstSearch();

  void breadthFirstSearch();

  bool isVisited(int row, int col);

public:
  pathfinder(int n, const std::vector<int> &gateStatus);
  void runDfsFromInjectionPoint();
  void runBfsFromInejectionPoint();
  std::vector<int> findPath(int row, int col);
};

#endif // !DFS_H
