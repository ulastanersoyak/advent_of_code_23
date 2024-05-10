#include <algorithm>
#include <array>
#include <cctype>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

std::array<char, 5> parse_nums(const std::string &arg) {
  std::array<char, 5> result;
  for (int i = 0; i < 5; i++) {
    result[i] = arg[i];
  }
  return result;
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
  std::string token;
  int rs = 0;
  while (std::getline(file, token)) {
    std::map<char, int> char_count;
    auto top5 = parse_nums(token.substr(token.find('[') + 1, 5));
    int checksum = std::stoi(token.substr(token.find('[') - 3, 3));
    for (const auto ch : token) {
      if (isdigit(ch)) {
        break;
      } else if (ch == '-') {
        continue;
      }
      char_count[ch] += 1;
    }
    std::vector<std::pair<char, int>> sorted_vec(char_count.begin(),
                                                 char_count.end());
    std::sort(sorted_vec.begin(), sorted_vec.end(),
              [](const auto &lhs, const auto &rhs) {
                return (lhs.second == rhs.second) ? (lhs.first < rhs.first)
                                                  : (lhs.second > rhs.second);
              });
    bool is_equal = true;
    for (int i = 0; i < 5; i++) {
      if (top5[i] != sorted_vec[i].first) {
        is_equal = false;
      }
    }
    if (is_equal) {
      rs += checksum;
    }
  }
  file.close();
  std::cout << rs;
  return 0;
}
