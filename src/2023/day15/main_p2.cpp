#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

int hash(const std::string &arg) {
  uint64_t local = 0;
  for (const auto ch : arg) {
    if (ch == '\n') {
      break;
    }
    local += ch;
    local = local * 17;
    local = local % 256;
  }
  return local;
}

int get_element_idx(const std::vector<std::pair<std::string, int>> &vec,
                    const std::string &arg) {
  for (int i = 0; i < vec.size(); i++) {
    if (vec[i].first == arg) {
      return i;
    }
  }
  return -1;
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
  std::string segment;
  std::vector<std::vector<std::pair<std::string, int>>> boxes;
  boxes.reserve(256);
  while (std::getline(file, segment, ',')) {
    bool add_op = false;
    std::string arg;
    if (segment.find('=') != std::string::npos) {
      arg = segment.substr(0, segment.find('='));
      add_op = true;
    } else {
      arg = segment.substr(0, segment.find('-'));
    }
    auto hash_rs = hash(arg);
    int idx = get_element_idx(boxes[hash_rs], arg);
    if (add_op) {
      if (idx == -1) {
        boxes[hash_rs].push_back(std::pair<std::string, int>{
            arg,
            std::stoi(segment.substr(segment.find('=') + 1, segment.size()))});
      } else {
        boxes[hash_rs][idx].second =
            std::stoi(segment.substr(segment.find('=') + 1, segment.size()));
      }
    } else {
      if (idx == -1) {
        continue;
      } else {
        boxes[hash_rs].erase(boxes[hash_rs].begin() + idx);
      }
    }
  }
  file.close();
  uint64_t rs = 0;
  for (int i = 0; i < boxes.capacity(); i++) {
    for (int j = 0; j < boxes[i].size(); j++) {
      int local = boxes[i][j].second * (i + 1) * (j + 1);
      rs += local;
    }
  }
  std::cout << rs;
  return 0;
}
