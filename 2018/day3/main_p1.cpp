#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <regex>
#include <string>

struct claim {
  int id;
  int x;
  int y;
  int width;
  int height;
};

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
  std::array<std::array<int, 1000>, 1000> fabric;
  for (auto &arr : fabric) {
    std::fill(arr.begin(), arr.end(), 0);
  }
  std::string line;
  std::regex pattern("#(\\d+) @ (\\d+),(\\d+): (\\d+)x(\\d+)");
  while (std::getline(file, line)) {
    claim current;
    std::sregex_iterator it(line.begin(), line.end(), pattern);
    std::sregex_iterator end;
    while (it != end) {
      std::smatch match = *it;
      current.id = std::stoi(match[1]);
      current.x = std::stoi(match[2]);
      current.y = std::stoi(match[3]);
      current.width = std::stoi(match[4]);
      current.height = std::stoi(match[5]);
      ++it;
    }
    for (int i = current.y; i < current.y + current.height; i++) {
      for (int j = current.x; j < current.x + current.width; j++) {
        fabric[i][j]++;
      }
    }
  }
  file.close();
  int rs = 0;
  for (int i = 0; i < fabric.size(); i++) {
    for (int j = 0; j < fabric[0].size(); j++) {
      if (fabric[i][j] > 1) {
        rs++;
      }
    }
  }
  std::cout << rs;
  return 0;
}
