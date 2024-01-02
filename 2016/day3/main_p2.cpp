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
  for (int i = 0; i < triangles[0].size(); i++) {
    for (int j = 2; j < triangles.size(); j++) {
      int s1 = triangles[j - 2][i];
      int s2 = triangles[j - 1][i];
      int s3 = triangles[j][i];
      if ((s1 / 100 == s2 / 100) && (s1 / 100 == s3 / 100) &&
          (s2 / 100 == s3 / 100)) {
        if ((s1 + s2) > s3 && (s1 + s3) > s2 && (s2 + s3) > s3) {
          valid_triangles++;
        }
      }
    }
  }
  std::cout << valid_triangles;
  return 0;
}
