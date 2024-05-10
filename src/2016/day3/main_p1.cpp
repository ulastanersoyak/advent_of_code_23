#include <array>
#include <fstream>
#include <iostream>
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
  int num1, num2, num3;
  std::vector<std::array<int, 3>> triangles;
  while (file >> num1 >> num2 >> num3) {
    triangles.emplace_back(std::array<int, 3>{num1, num2, num3});
  }
  file.close();
  int valid_triangles = 0;
  for (const auto &triangle : triangles) {
    if ((triangle[0] + triangle[1]) > triangle[2] &&
        (triangle[0] + triangle[2]) > triangle[1] &&
        (triangle[1] + triangle[2]) > triangle[0]) {
      valid_triangles++;
    }
  }
  std::cout << valid_triangles;
  return 0;
}
