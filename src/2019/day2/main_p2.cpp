#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
  std::string num;
  std::vector<int> opcode;
  while (std::getline(file, num, ',')) {
    opcode.push_back(std::stoi(num));
  }
  file.close();
  for (int j = 0; j < 100; j++) {
    for (int k = 0; k < 100; k++) {
      std::vector<int> current_opcode{opcode};
      current_opcode[1] = j;
      current_opcode[2] = k;
      for (int i = 0; i < current_opcode.size(); i += 4) {
        if (current_opcode[i] == 99) {
          break;
        } else if (current_opcode[i] == 1) {
          current_opcode[current_opcode[i + 3]] =
              current_opcode[current_opcode[i + 1]] +
              current_opcode[current_opcode[i + 2]];
        } else if (current_opcode[i] == 2) {
          current_opcode[current_opcode[i + 3]] =
              current_opcode[current_opcode[i + 1]] *
              current_opcode[current_opcode[i + 2]];
        }
      }
      if (current_opcode[0] == 19690720) {
        std::cout << 100 * j + k;
      }
    }
  }
  return 0;
}
