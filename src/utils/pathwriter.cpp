#include "utils/pathwriter.h"
#include <fstream>
#include <iostream>
#include <string>

int writePathToCsv(std::vector<int> &path, int n, const std::string &filename) {
  std::ofstream csv_file(filename);

  if (!csv_file.is_open()) {
    std::cerr << "Error Opening file.";
    return 1;
  }

  csv_file << "Step, Row, Col\n";

  for (auto step{0}; step < path.size(); step++) {
    int index = path[step];
    int row = index / n;
    int col = index % n;

    csv_file << step << ',' << row << ',' << col << '\n';
  }

  return 0;
}

std::string filename(int trialNumber) {
  return "trialPaths/path_trial" + std::to_string(trialNumber) + ".csv";
}
