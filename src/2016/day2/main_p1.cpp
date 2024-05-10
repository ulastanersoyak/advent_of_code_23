#include <array>
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
  std::array<std::array<int, 3>, 3> keypad{{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}}};
  std::vector<std::pair<int, int>> rs_vec;
  while (std::getline(file, line)) {
    std::pair<int, int> pos{1, 1};
    for (int i = 0; i < line.length(); i++) {
      char direction = line[i];
      switch (direction) {
      case 'U':
        if (pos.first != 0) {
          pos.first--;
        }
        break;
      case 'D':
        if (pos.first != 2) {
          pos.first++;
        }
        break;
      case 'L':
        if (pos.second != 0) {
          pos.second--;
        }
        break;
      case 'R':
        if (pos.second != 2) {
          pos.second++;
        }
        break;
      }
    }
    rs_vec.push_back(pos);
  }

  file.close();
  for (const auto &[x, y] : rs_vec) {
    std::cout << keypad[x][y];
  }
  return 0;
}
