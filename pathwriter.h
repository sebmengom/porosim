#ifndef PATHWRITER_H
#define PATHWRITER_H

#include <string>
#include <vector>
int writePathToCsv(std::vector<int> &path, int n, const std::string &filename);
std::string filename(int trialNumber);

#endif // !PATHWRITER_H
