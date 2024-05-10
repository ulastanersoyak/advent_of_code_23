#include <climits>
#include <fstream>
#include <iostream>
#include <map>
#include <regex>
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
  std::map<std::string, int> reg_map;
  std::regex pattern(R"((\w+) (inc|dec) (-?\d+) if (\w+) ([!=<>]+) (-?\d+))");
  int biggest = INT_MIN;
  while (std::getline(file, line)) {
    auto begin = std::sregex_iterator(line.begin(), line.end(), pattern);
    auto end = std::sregex_iterator();
    for (std::sregex_iterator iter = begin; iter != end; ++iter) {
      const std::smatch &match = *iter;
      std::string tar_reg = match[1].str();
      bool ar_op = match[2].str() == "inc" ? 1 : 0;
      int tar_val = std::stoi(match[3].str());
      std::string flag_reg = match[4].str();
      std::string con_op = match[5].str();
      int con_val = std::stoi(match[6].str());

      if (reg_map.find(tar_reg) == reg_map.end()) {
        reg_map[tar_reg] = 0;
      }
      if (reg_map.find(flag_reg) == reg_map.end()) {
        reg_map[flag_reg] = 0;
      }
      tar_val = ar_op ? tar_val : tar_val * -1;
      if (con_op == "==") {
        if (reg_map.at(flag_reg) == con_val) {
          reg_map.at(tar_reg) += tar_val;
        }
      } else if (con_op == "!=") {
        if (reg_map.at(flag_reg) != con_val) {
          reg_map.at(tar_reg) += tar_val;
        }
      } else if (con_op == ">=") {
        if (reg_map.at(flag_reg) >= con_val) {
          reg_map.at(tar_reg) += tar_val;
        }
      } else if (con_op == "<=") {
        if (reg_map.at(flag_reg) <= con_val) {
          reg_map.at(tar_reg) += tar_val;
        }
      } else if (con_op == ">") {
        if (reg_map.at(flag_reg) > con_val) {
          reg_map.at(tar_reg) += tar_val;
        }
      } else if (con_op == "<") {
        if (reg_map.at(flag_reg) < con_val) {
          reg_map.at(tar_reg) += tar_val;
        }
      }
    }
    for (const auto &[key, value] : reg_map) {
      if (value > biggest)
        biggest = value;
    }
  }
  file.close();
  std::cout << biggest;
  return 0;
}
