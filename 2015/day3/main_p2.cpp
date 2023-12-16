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
  std::pair<int, int> santa_current{0, 0};
  std::pair<int, int> robo_current{0, 0};
  bool is_santa = true;
  lookup[santa_current] = 2;
  for (const auto &ch : line) {
    switch (ch) {
    case '>':
      if (is_santa) {
        santa_current.second += 1;
        lookup[santa_current] += 1;
        break;
      } else {
        robo_current.second += 1;
        lookup[robo_current] += 1;
        break;
      }
    case '<':
      if (is_santa) {
        santa_current.second -= 1;
        lookup[santa_current] += 1;
        break;
      } else {
        robo_current.second -= 1;
        lookup[robo_current] += 1;
        break;
      }

    case 'v':
      if (is_santa) {
        santa_current.first += 1;
        lookup[santa_current] += 1;
        break;
      } else {
        robo_current.first += 1;
        lookup[robo_current] += 1;
        break;
      }
    case '^':
      if (is_santa) {
        santa_current.first -= 1;
        lookup[santa_current] += 1;
        break;
      } else {
        robo_current.first -= 1;
        lookup[robo_current] += 1;
        break;
      }
    }
    is_santa = (is_santa) ? false : true;
  }
  std::cout << lookup.size();
  return 0;
}
