#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<int>
parse_num (int arg)
{
  std::vector<int> rs;
  while (arg > 0)
    {
      rs.push_back (arg % 10);
      arg = arg / 10;
    }
  std::reverse (rs.begin (), rs.end ());
  return rs;
}

bool
is_valid (int arg)
{
  auto vec = parse_num (arg);
  bool rs = true;
  bool adjsame = false;
  for (int i = 1; i < vec.size (); i++)
    {
      if ((vec[i] == vec[i - 1]) && !adjsame)
        {
          adjsame = true;
        }
      if (vec[i] < vec[i - 1])
        {
          rs = false;
          break;
        }
    }
  return adjsame && rs;
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
  std::string range;
  std::getline (file, range);
  file.close ();
  int bottom = std::stoi (range.substr (0, range.find ('-')));
  int top = std::stoi (range.substr (range.find ('-') + 1, range.size ()));
  int rs = 0;
  for (int i = bottom + 1; i < top; i++)
    {
      rs = is_valid (i) ? rs + 1 : rs;
    }
  std::cout << rs;
  return 0;
}
