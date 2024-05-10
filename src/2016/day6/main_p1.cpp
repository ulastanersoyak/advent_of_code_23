#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
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
  std::string line;
  std::vector<std::string> all_words;
  while (std::getline(file, line)) {
    all_words.push_back(line);
  }
  file.close();
  for (int i = 0; i < all_words[0].size(); i++) {
    std::map<char, int> lookup;
    for (int j = 0; j < all_words.size(); j++) {
      lookup[all_words[j][i]] += 1;
    }
    auto max_pair = *std::max_element(
        lookup.begin(), lookup.end(),
        [](const auto &a, const auto &b) { return a.second < b.second; });
    std::cout << max_pair.first;
  }
  return 0;
}
