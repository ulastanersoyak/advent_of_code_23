#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
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
  int rs = 0;
  while (std::getline(file, line)) {
    std::vector<int> dimentions;
    std::istringstream iss(line);
    std::string temp;
    while (std::getline(iss, temp, 'x')) {
      dimentions.push_back(std::stoi(temp));
    }
    rs += (2 * dimentions[0] * dimentions[1]) +
          (2 * dimentions[1] * dimentions[2]) +
          (2 * dimentions[0] * dimentions[2]);
    std::sort(dimentions.begin(), dimentions.end());
    rs += dimentions[0] * dimentions[1];
  }
  std::cout << rs;
  file.close();
  return 0;
}
