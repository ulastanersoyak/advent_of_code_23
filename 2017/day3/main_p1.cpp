#include <fstream>
#include <iostream>
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
  std::getline(file, line);
  file.close();
  int number = std::stoi(line);
  int i = 0;
  while ((i * i) < number) {
    i++;
  }
  int lbottom_cor = (i * i);
  int center = ((i - 1) / 2);
  std::cout << center + center - (lbottom_cor - number);
  return 0;
}
