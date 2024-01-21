#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

struct cable_part {
  int x;
  int y;
  int step;
};

std::vector<std::pair<char, int>> parse_line(const std::string &arg) {
  std::istringstream ss(arg);
  std::vector<std::pair<char, int>> result;
  std::string token;

  while (std::getline(ss, token, ',')) {
    char prefix = token[0];
    int value = std::stoi(token.substr(1));
    result.push_back(std::make_pair(prefix, value));
  }
  return result;
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
  while (std::getline(file, line)) {
    auto parsed_line = parse_line(line);
  }
  return 0;
}
