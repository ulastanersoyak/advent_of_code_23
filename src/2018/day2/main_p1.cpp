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
  int twos = 0;
  int threes = 0;
  while (std::getline (file, line))
    {
      bool found_two = false;
      bool found_three = false;
      std::map<char, int> line_chars;
      for (const auto ch : line)
        {
          line_chars[ch] += 1;
        }
      for (const auto [key, value] : line_chars)
        {
          if (value == 2)
            {
              found_two = true;
            }
          else if (value == 3)
            {
              found_three = true;
            }
        }
      if (found_two)
        {
          twos++;
        }
      if (found_three)
        {
          threes++;
        }
    }
  file.close ();
  std::cout << twos * threes;
  return 0;
}
