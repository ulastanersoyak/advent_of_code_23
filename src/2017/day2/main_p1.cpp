#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> parse_line(const std::string &arg) {
  std::vector<int> rs;
  std::istringstream iss(arg);
  int number;
  while (iss >> number) {
    rs.push_back(number);
  }
  return rs;
}

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " <filename>\n";
    return -1;
  }
  std::ifstream file{argv[1]};
  if (!file) {
    std::cerr << "failed to open file " << argv[1];
    return -1;
  }
  std::string line;
  int rs = 0;
  while (std::getline(file, line)) {
    auto vec = parse_line(line);
    std::sort(vec.begin(), vec.end());
    rs += (vec[vec.size()] - vec[0]);
  }
  std::cout << rs;
  file.close();
  return 0;
}
