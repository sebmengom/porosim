#include "utils/pathwriter.h"
#include <cstddef>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>

int writePathToCsv(std::vector<int> &path, int n, const std::string &filename) {
  std::filesystem::path dir_path{"trialPaths/"};
  try {
    std::filesystem::create_directories(dir_path);
  } catch (const std::filesystem::filesystem_error &e) {
    std::cerr << "Error creating dir." << e.what() << '\n';
  }
  std::ofstream csv_file(filename);

  if (!csv_file.is_open()) {
    std::cerr << "Error Opening file.";
    return 1;
  }

  csv_file << "Step, Row, Col\n";

  for (std::size_t step{0}; step < path.size(); step++) {
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
