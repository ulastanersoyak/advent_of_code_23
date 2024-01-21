#include <fstream>
#include <iostream>
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
  int prev = 0;
  int rs = 0;
  while (std::getline(file, line)) {
    rs = (std::stoi(line) > prev) ? rs + 1 : rs;
    prev = std::stoi(line);
  }
  std::cout << rs - 1;
  file.close();
  return 0;
}
