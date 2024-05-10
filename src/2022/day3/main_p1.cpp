#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>

int
map_val (char ch)
{
  if (ch > 96)
    {
      return ch - 96;
    }
  return ch - 38;
}

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
  int rs = 0;
  while (std::getline (file, line))
    {
      std::string comp1 = line.substr (0, line.size () / 2);
      std::string comp2 = line.substr (line.size () / 2, line.size () / 2);
      std::sort (comp1.begin (), comp1.end ());
      std::sort (comp2.begin (), comp2.end ());
      std::string common_chars;
      std::set_intersection (comp1.begin (), comp1.end (), comp2.begin (),
                             comp2.end (), std::back_inserter (common_chars));
      int temp = map_val (common_chars[0]);
      rs += temp;
    }
  std::cout << rs;
  return 0;
}
