#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<int> stoiv(const std::string &arg) {
  std::vector<int> rs;
  int local = 0;
  for (const auto &ch : arg) {
    if (ch == ',') {
      rs.push_back(local);
      local = 0;
      continue;
    }
    local = (local * 10) + (ch - '0');
  }
  rs.push_back(local);
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
  while (std::getline(file, line)) {
    auto gears = line.substr(0, line.find(' '));
    auto gear_seq =
        stoiv(line.substr(line.find(' ') + 1, line.size() - line.find(' ')));
    break;
  }
  return 0;
}
