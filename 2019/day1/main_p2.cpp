#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

inline int calc_fuel(int arg) { return std::floor(arg / 3) - 2; }

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
  int total_fuel = 0;
  while (std::getline(file, line)) {
    int local_fuel = calc_fuel(std::stoi(line));
    while (1) {
      total_fuel += local_fuel;
      local_fuel = calc_fuel(local_fuel);
      if (local_fuel <= 0) {
        break;
      }
    }
  }
  file.close();
  std::cout << total_fuel;
  return 0;
}
