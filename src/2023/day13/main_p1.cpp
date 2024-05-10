#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::string>
transpose (const std::vector<std::string> &arg)
{
  std::vector<std::string> ret_val;
  for (int i = 0; i < arg[0].size (); i++)
    {
      std::string str;
      for (const auto &j : arg)
        {
          str = str + j[i];
        }
      ret_val.push_back (str);
    }
  return ret_val;
}

int
find_mirrors (const std::vector<std::string> &map)
{
  int rows = map.size ();
  for (int i = 1; i < map.size (); i++)
    {
      bool mirror_found = true;
      int rowstocompare = std::min (i, rows - i);
      for (int j = 0; j < rowstocompare; j++)
        {
          if (!mirror_found)
            {
              break;
            }
          const std::string &top = map[i - 1 - j];
          const std::string &bot = map[i + j];
          if (top != bot)
            {
              mirror_found = false;
            }
        }
      if (mirror_found)
        {
          return i;
        }
    }
  return 0;
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
  std::vector<std::string> lava_map;
  int rs = 0;
  while (std::getline (file, line))
    {
      if (line.empty ())
        {
          rs += find_mirrors (lava_map) * 100;
          auto x = transpose (lava_map);
          rs += find_mirrors (transpose (lava_map));
          lava_map.erase (lava_map.begin (), lava_map.end ());
          continue;
        }
      lava_map.push_back (line);
    }
  std::cout << rs;
  file.close ();
  return 0;
}
