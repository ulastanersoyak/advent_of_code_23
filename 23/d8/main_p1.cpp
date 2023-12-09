#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>

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
  std::map<std::string, std::pair<std::string, std::string>> dir_map;
  std::string directions;
  std::getline(file, directions);
  std::string line;
  std::getline(file, line);
  while (std::getline(file, line)) {
    dir_map[line.substr(0, line.find('=') - 1)] =
        std::pair<std::string, std::string>{line.substr(line.find('(') + 1, 3),
                                            line.substr(line.find(',') + 2, 3)};
  }
  int steps = 0;
  std::string current_pos = "AAA";
  while (current_pos[0] != 'Z') {
    current_pos = (directions[steps % directions.length()] == 'L')
                      ? dir_map[current_pos].first
                      : dir_map[current_pos].second;
    steps++;
  }
  std::cout << "final output: " << steps;
  return 0;
}
