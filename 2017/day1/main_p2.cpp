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
  int padding = line.size() / 2;
  for (int i = 0; i < line.size(); i++) {
    int check_idx = (i + padding) % line.size();
    if (line[i] == line[check_idx]) {
      rs += line[i] - '0';
    }
  }
  std::cout << rs;
  return 0;
}
