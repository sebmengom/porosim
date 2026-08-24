
#include <iostream>
#include <random>
int main() {
  std::random_device rd;
  std::mt19937 machine{rd()};
  std::uniform_real_distribution<double> distribution(0, 1);
  std::cout << machine;
}
