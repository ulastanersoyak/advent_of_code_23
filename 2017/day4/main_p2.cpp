#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string> parse_line(const std::string &arg) {
  std::vector<std::string> rs;
  std::istringstream iss(arg);
  std::string token;
  while (iss >> token) {
    rs.push_back(token);
  }
  return rs;
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
  int result = 0;
  while (std::getline(file, token)) {
    bool is_valid = true;
    auto parsed_line = parse_line(token);
    std::map<std::vector<char>, int> lookup;
    for (const auto &word : parsed_line) {
      std::vector<char> all_chars;
      for (const auto &ch : word) {
        all_chars.push_back(ch);
      }
      std::sort(all_chars.begin(), all_chars.end());
      lookup[all_chars] += 1;
      if (lookup.at(all_chars) > 1) {
        is_valid = false;
        break;
      }
    }
    if (is_valid) {
      result++;
    }
  }
  file.close();
  std::cout << result;
  return 0;
}
