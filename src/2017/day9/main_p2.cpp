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
  int rs = 0;
  bool inside_trash = false;
  bool skip_char = false;
  int trash = 0;
  for (int i = 0; i < line.size(); i++) {
    if (inside_trash) {
      if (skip_char) {
        skip_char = false;
      } else if (line[i] == '!') {
        skip_char = true;
      } else if (line[i] == '>') {
        inside_trash = false;
      } else {
        trash++;
      }
    } else {
      if (line[i] == '{') {
      } else if (line[i] == '}') {
      } else if (line[i] == '<') {
        inside_trash = true;
      }
    }
  }
  std::cout << trash;
  return 0;
}
