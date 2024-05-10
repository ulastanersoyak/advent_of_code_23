#include <fstream>
#include <iostream>
#include <map>
#include <string>

bool does_have_repeating_char(const std::string &arg) {
  for (int i = 1; i < arg.size(); i++) {
    if (arg[i] == arg[i - 1]) {
      return true;
    }
  }
  return false;
}

bool does_have_magic_seq(const std::string &arg) {
  int rs = 0;
  rs = arg.find("ab") + arg.find("cd") + arg.find("pq") + arg.find("xy");
  if (rs == -4) {
    return true;
  }
  return false;
}

bool does_have_three_vowels(const std::string &arg) {
  std::map<char, int> vowel_map{
      {'a', 1}, {'e', 1}, {'o', 1}, {'i', 1}, {'u', 1}};
  int vowel_count = 0;
  for (int i = 0; i < arg.size(); i++) {
    vowel_count += vowel_map[arg[i]];
  }
  if (vowel_count < 3) {
    return false;
  }
  return true;
}
bool is_nice(const std::string &arg) {
  bool result = true;
  result = result && does_have_three_vowels(arg);
  result = result && does_have_repeating_char(arg);
  result = result && does_have_magic_seq(arg);
  return result;
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
  int rs = 0;
  while (std::getline(file, line)) {
    if (is_nice(line)) {
      rs++;
    }
  }
  file.close();
  std::cout << rs;
  return 0;
}
