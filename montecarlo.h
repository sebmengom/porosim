#ifndef montecarlo_h
#define montecarlo_h

#include "dsu.h"
#include <random>
#include <string>
#include <utility>
#include <vector>
class montecarlo {
private:
  std::vector<double> p{0.10, 0.20,  0.30, 0.40, 0.45, 0.50, 0.55, 0.57, 0.58,
                        0.59, 0.593, 0.60, 0.61, 0.63, 0.65, 0.70, 0.80, 0.90};
  int gridSize{};
  int numberOfTrials{};
  std::random_device rd;
  std::mt19937 machine{rd()};
  std::uniform_real_distribution<double> distribution{0, 1};
  std::vector<std::pair<double, double>> results{};
  std::vector<double> newResults{};
  int sizeOfP{static_cast<int>(p.size())};

public:
  montecarlo(int gridSize, int numberOfTrials);
  void trials();
  bool singleTrial(double pItem);
  void printResults();
  void newTrials();
  double newSingleTrial();
  void printNewResults();
};

#endif // !montecarlo_h
