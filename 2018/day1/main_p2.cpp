#include <fstream>
#include <iostream>
#include <map>
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
  std::vector<int> instructions;
  while (std::getline(file, line)) {
    instructions.push_back(std::stoi(line));
  }
  file.close();
  int rs = 0;
  std::map<int, int> hashmap;
  for (int i = 0;; i++) {
    rs += instructions[i % instructions.size()];
    hashmap[rs] += 1;
    if (hashmap.at(rs) > 1) {
      std::cout << rs;
      break;
    }
  }
  return 0;
}
