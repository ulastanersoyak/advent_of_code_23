#include <fstream>
#include <iostream>
#include <string>
#include <vector>

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
  std::vector<std::string> map;
  while (std::getline (file, line))
    {
      map.push_back (line);
    }

  for (int i = 0; i < map.size (); i++)
    {
      for (int j = 0; j < map[0].size (); j++)
        {
          if (map[i][j] == 'O' && i != 0)
            {
              int x_pos = i;
              while (x_pos > 0 && map[x_pos - 1][j] == '.')
                {
                  map[x_pos - 1][j] = 'O';
                  map[x_pos][j] = '.';
                  x_pos--;
                }
            }
        }
    }

  int rs = 0;
  for (int i = 0; i < map.size (); i++)
    {
      for (int j = 0; j < map[0].size (); j++)
        {
          int x_pos = i;
          bool does_contribute = true;
          if (map[i][j] == 'O')
            {
              rs += map.size () - i;
            }
        }
    }
  for (const auto &x : map)
    {
      std::cout << x << '\n';
    }
  std::cout << rs;
  file.close ();
  return 0;
}
