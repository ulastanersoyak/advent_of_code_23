#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

int get_stack_count(const std::string &arg) {
  return arg[arg.size() - 1] - '0';
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
  std::array<std::vector<char>, 10> crates;
  std::vector<std::string> instr;
  bool init = true;
  while (std::getline(file, line)) {
    if (line == "" || line[1] == '1') {
      init = false;
      continue;
    }
    if (init) {
      for (int i = 1; i < line.size(); i += 4) {
        if (line[i] != ' ') {
          crates[i / 4].push_back(line[i]);
        }
      }
    } else {

      instr.push_back(line);
    }
  }
  for (auto &crate : crates) {
    std::reverse(crate.begin(), crate.end());
  }
  for (auto line : instr) {
    int times = line[5] - '0';
    int from = (line[12] - '0') - 1;
    int to = (line[17] - '0') - 1;
    int count = crates[from].size();
    for (int i = 0; i < times; i++) {
      crates[to].push_back(crates[from].back());
      crates[from].pop_back();
    }
    std::cout << line << '\n';
  }
  for (auto x : crates) {
    std::cout << x.back();
  }
  return 0;
}
