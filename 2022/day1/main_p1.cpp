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
  int max_cal = 0;
  std::string line;
  int cur_cal = 0;
  while (std::getline(file, line)) {
    if (line == "") {
      if (cur_cal > max_cal) {
        max_cal = cur_cal;
      }
      cur_cal = 0;
    }
    int x = 0;
    for (const auto &ch : line) {
      x = (x * 10) + (ch - '0');
    }
    cur_cal += x;
  }
  std::cout << max_cal;
  return 0;
}
