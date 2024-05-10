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
    std::map<std::string, int> hashmap;
    bool is_passphrase = true;
    std::vector<std::string> rs = parse_line(token);
    for (int i = 0; i < rs.size(); i++) {
      hashmap[rs[i]] += 1;
      if (hashmap.at(rs[i]) > 1) {
        is_passphrase = false;
        break;
      }
    }
    if (is_passphrase) {
      result++;
    }
  }
  file.close();
  std::cout << result;
  return 0;
}
