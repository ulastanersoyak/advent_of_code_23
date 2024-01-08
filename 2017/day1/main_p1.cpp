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
  file.close();
  int rs = 0;
  for (int i = 0; i <= line.size(); i++) {
    if (i == line.size() - 1) {
      if (line[i] == line[0]) {
        rs += line[i] - '0';
        break;
      }
    } else {
      if (line[i] == line[i + 1]) {
        rs += line[i] - '0';
      }
    }
  }
  std::cout << rs;
  return 0;
}
