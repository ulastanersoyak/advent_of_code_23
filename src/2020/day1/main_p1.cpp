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
  std::map<int, int> lookup;
  while (std::getline (file, line))
    {
      lookup[std::stoi (line)] += 1;
    }
  file.close ();
  for (const auto [num, occur] : lookup)
    {
      int look = 2020 - num;
      if (lookup.count (look) > 0)
        {
          std::cout << num * look;
          break;
        }
    }
  return 0;
}
