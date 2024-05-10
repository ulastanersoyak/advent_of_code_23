#include <fstream>
#include <iostream>
#include <map>
#include <string>

int
main (int argc, char **argv)
{
  if (argc < 2)
    {
      std::cerr << "usage: " << argv[0] << " <filename>\n";
      return -1;
    }
  std::ifstream file{ argv[1] };
  if (!file)
    {
      std::cerr << "failed to open file " << argv[1];
      return -1;
    }
  std::string line;
  std::getline (file, line);
  file.close ();
  int number = std::stoi (line);
  std::map<std::pair<int, int>, int> lookup;
  int current_number = 1;
  int side_len = 1;
  std::pair<int, int> current_pos{ 0, 0 };
  while (current_number < number)
    {
      lookup[current_pos] = current_number;
    }
  return 0;
}
