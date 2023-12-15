#include <array>
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
  std::getline(file, line);
  int rs = 0;
  for (const auto &ch : line) {
    int direction = (ch == '(') ? 1 : -1;
    rs += direction;
  }
  std::cout << rs;
  file.close();
  return 0;
}
