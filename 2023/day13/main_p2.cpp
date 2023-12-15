#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string> transpose(const std::vector<std::string> &arg) {
  std::vector<std::string> ret_val;
  for (int i = 0; i < arg[0].size(); i++) {
    std::string str = "";
    for (int j = 0; j < arg.size(); j++) {
      str = str + arg[j][i];
    }
    ret_val.push_back(str);
  }
  return ret_val;
}

int char_diff(const std::string &s1, const std::string &s2) {
  int rs = 0;
  for (int i = 0; i < s1.length(); i++) {
    if (s1[i] != s2[i]) {
      rs++;
    }
  }
  return rs;
}

int find_mirrors(const std::vector<std::string> &map) {
  int rows = map.size();
  for (int i = 1; i < map.size(); i++) {
    int dif = 0;
    int rowstocompare = std::min(i, rows - i);
    for (int j = 0; j < rowstocompare; j++) {
      std::string top = map[i - 1 - j];
      std::string bot = map[i + j];
      dif += char_diff(top, bot);
    }
    if (dif == 1) {
      return i;
    }
  }
  return 0;
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
  std::vector<std::string> lava_map;
  int rs = 0;
  while (std::getline(file, line)) {
    if (line == "") {
      rs += find_mirrors(lava_map) * 100;
      auto x = transpose(lava_map);
      rs += find_mirrors(transpose(lava_map));
      lava_map.erase(lava_map.begin(), lava_map.end());
      continue;
    }
    lava_map.push_back(line);
  }
  std::cout << rs;
  file.close();
  return 0;
}
