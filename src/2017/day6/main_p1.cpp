#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

std::vector<int> parse_line(const std::string &arg) {
  std::vector<int> rs;
  std::istringstream iss(arg);
  std::string token;
  while (iss >> token) {
    rs.push_back(std::stoi(token));
  }
  return rs;
}

void redistribute(std::vector<int> &vec, int idx, int batteries) {
  idx++;
  while (batteries > 0) {
    vec[idx % vec.size()] += 1;
    batteries--;
    idx++;
  }
}

int find_biggest_idx(const std::vector<int> &arg) {
  int biggest = INT_MIN;
  int rs = 0;
  for (int i = 0; i < arg.size(); i++) {
    if (arg[i] > biggest) {
      biggest = arg[i];
      rs = i;
    }
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
  std::string line;
  std::getline(file, line);
  file.close();
  auto banks = parse_line(line);
  int step = 0;
  std::map<std::vector<int>, int> hashmap;
  while (1) {
    hashmap[banks] += 1;
    if (hashmap.at(banks) > 1) {
      break;
    }
    auto idx = find_biggest_idx(banks);
    int batteries = banks[idx];
    banks[idx] = 0;
    redistribute(banks, idx, batteries);
    step++;
  }
  std::cout << step;
  return 0;
}
