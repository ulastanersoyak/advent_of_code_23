#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

std::vector<int>
parse_line (const std::string &arg)
{
  std::vector<int> rs;
  std::istringstream iss (arg);
  int number = 0;
  while (iss >> number)
    {
      rs.push_back (number);
    }
  return rs;
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
      auto vec = parse_line (line);
      for (int i = 0; i < vec.size () - 1; i++)
        {
          for (int j = i + 1; j < vec.size (); j++)
            {
              if (vec[i] % vec[j] == 0)
                {
                  rs += vec[i] / vec[j];
                }
              else if (vec[j] % vec[i] == 0)
                {
                  rs += vec[j] / vec[i];
                }
            }
        }
    }
  std::cout << rs;
  file.close ();
  return 0;
}
