#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <iterator>
#include <numeric>
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
  int cur_cal = 0;
  int rs = 0;
  std::array<int, 3> top_3 = {0, 0, 0};
  while (std::getline(file, line)) {
    if (line == "") {
      auto min_idx =
          std::min_element(top_3.begin(), top_3.end()) - top_3.begin();
      auto min = *std::min_element(top_3.begin(), top_3.end());
      if (cur_cal > min) {
        top_3[min_idx] = cur_cal;
      }
      cur_cal = 0;
      continue;
    }
    int x = 0;
    for (const auto &ch : line) {
      x = (x * 10) + (ch - '0');
    }
    cur_cal += x;
  }
  rs = std::accumulate(top_3.begin(), top_3.end(), 0);
  std::cout << rs;
  return 0;
}
