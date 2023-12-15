#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int hash(const std::string &arg) {
  uint64_t local = 0;
  for (const auto ch : arg) {
    if (ch == '\n') {
      break;
    }
    local += ch;
    local = local * 17;
    local = local % 256;
  }
  return local;
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
  std::string segment;
  uint64_t sum = 0;
  while (std::getline(file, segment, ',')) {
    std::cout << segment << '\n';
    auto local = hash(segment);
    sum += local;
  }
  std::cout << sum;
  file.close();
  return 0;
}
