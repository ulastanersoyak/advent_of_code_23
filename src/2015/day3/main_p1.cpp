#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>

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
  std::getline(file, line);
  file.close();
  std::map<std::pair<int, int>, int> lookup;
  std::pair<int, int> current{0, 0};
  lookup[current] = 1;
  for (const auto &ch : line) {
    switch (ch) {
    case '>':
      current.second += 1;
      lookup[current] += 1;
      break;
    case '<':
      current.second -= 1;
      lookup[current] += 1;
      break;
    case 'v':
      current.first += 1;
      lookup[current] += 1;
      break;
    case '^':
      current.first -= 1;
      lookup[current] += 1;
      break;
    }
  }
  std::cout << lookup.size();
  return 0;
}
