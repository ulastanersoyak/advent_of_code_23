#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <string>
#include <vector>

int map_val(char ch) {
  if (ch > 96) {
    return ch - 96;
  }
  return ch - 38;
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
  std::vector<std::string> all_lines;
  while (std::getline(file, line)) {
    all_lines.push_back(line);
  }
  int rsx = 0;
  for (int i = 1; i < all_lines.size() - 1; i += 3) {
    std::string first = all_lines[i - 1];
    std::string second = all_lines[i];
    std::string third = all_lines[i + 1];
    std::sort(first.begin(), first.end());
    std::sort(second.begin(), second.end());
    std::sort(third.begin(), third.end());
    std::string common_char;
    std::set_intersection(first.begin(), first.end(), second.begin(),
                          second.end(), std::back_inserter(common_char));
    std::string rs;
    std::set_intersection(third.begin(), third.end(), common_char.begin(),
                          common_char.end(), std::back_inserter(rs));
    std::cout << rs << '\n';
    rsx += map_val(rs[0]);
  }
  std::cout << rsx;
  return 0;
}
