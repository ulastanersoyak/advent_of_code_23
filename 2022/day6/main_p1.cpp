#include <fstream>
#include <iostream>
#include <numeric>
#include <set>
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
  std::vector<int> buffer_sizes;
  while (std::getline(file, line)) {
    std::set<char> chars;
    for (int i = 0; i < line.size() - 4; i++) {
      for (int j = 0; j < 4; j++) {
        chars.insert(line[i + j]);
      }
      if (chars.size() == 4) {
        buffer_sizes.push_back(i + 4);
        chars.clear();
        break;
      } else {
        chars.clear();
      }
    }
  }
  for (auto x : buffer_sizes) {
    std::cout << x << '\n';
  }
  // std::cout << std::accumulate(buffer_sizes.begin(), buffer_sizes.end(), 0);
  return 0;
}
