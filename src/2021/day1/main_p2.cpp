#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
  std::vector<int> vec;
  while (std::getline(file, line)) {
    vec.push_back(std::stoi(line));
  }
  int rs = 0;
  int prev = 0;
  for (int i = 1; i < vec.size() - 1; i++) {
    int current = vec[i - 1] + vec[i] + vec[i + 1];
    rs = current > prev ? rs + 1 : rs;
    prev = current;
  }
  std::cout << rs - 1;
  file.close();
  return 0;
}
