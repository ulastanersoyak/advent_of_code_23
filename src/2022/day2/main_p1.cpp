#include <fstream>
#include <iostream>
#include <map>
#include <string>

#define WIN 6
#define LOSE 0
#define DRAW 3

int match_rs(char om, char mm) {
  if (mm == om) {
    return DRAW;
  } else if ((mm == 'R' && om == 'S') || (mm == 'P' && om == 'R') ||
             (mm == 'S' && om == 'P')) {
    return WIN;
  }
  return LOSE;
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
  std::map<char, char> move_lookup = {{'A', 'R'}, {'B', 'P'}, {'C', 'S'},
                                      {'X', 'R'}, {'Y', 'P'}, {'Z', 'S'}};

  std::map<char, int> score_lookup = {{'R', 1}, {'P', 2}, {'S', 3}};
  std::string line;
  int total_rs = 0;
  while (std::getline(file, line)) {
    int rs = match_rs(move_lookup[line[0]], move_lookup[line[2]]);
    total_rs += rs + score_lookup[move_lookup[line[2]]];
  }
  std::cout << total_rs;
  return 0;
}
