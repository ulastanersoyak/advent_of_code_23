#include <array>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <map>
#include <numeric>
#include <regex>
#include <string>
#include <utility>
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
  std::map<std::string, std::pair<std::string, std::string>> dir_map;
  std::string directions;
  std::getline(file, directions);
  std::string line;
  std::getline(file, line);
  std::vector<std::string> start_paths;
  while (std::getline(file, line)) {
    std::string node = line.substr(0, line.find('=') - 1);
    dir_map[node] = std::pair<std::string, std::string>{
        line.substr(line.find('(') + 1, 3), line.substr(line.find(',') + 2, 3)};
    if (node[2] == 'A') {
      start_paths.push_back(node);
    }
  }
  for (int i = 0; i < start_paths.size(); i++) {
    std::cout << start_paths[i] << ' ';
  }

  std::vector<int> rs_vec;
  for (int i = 0; i < start_paths.size(); i++) {
    std::string current_pos = start_paths[i];
    int j = 0;
    for (; current_pos[2] != 'Z'; j++) {
      current_pos = (directions[j % directions.length()] == 'L')
                        ? dir_map[current_pos].first
                        : dir_map[current_pos].second;
    }
    rs_vec.push_back(j);
  }
  uint64_t lcm = 1;
  for (int i = 0; i < rs_vec.size(); i++) {
    lcm = std::lcm(rs_vec[i], lcm);
  }
  std::cout << lcm;
  return 0;
}
