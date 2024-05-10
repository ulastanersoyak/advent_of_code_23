#include <fstream>
#include <iostream>
#include <string>
#include <vector>

bool
find_rev_pair (const std::string &arg)
{
  for (int i = 3; i < arg.length (); i++)
    {
      if ((arg[i] == arg[i - 3]) && (arg[i - 1] == arg[i - 2])
          && (arg[i] != arg[i - 1]))
        {
          return true;
        }
    }
  return false;
}

std::vector<std::string>
parse_line (const std::string &arg)
{
  std::vector<std::string> rs;
  std::string str;
  bool is_valid = true;
  for (const char ch : arg)
    {
      if (ch == '[')
        {
          rs.push_back (str);
          is_valid = false;
        }
      else if (ch == ']')
        {
          str.clear ();
          is_valid = true;
          continue;
        }
      if (is_valid)
        {
          str += ch;
        }
    }
  rs.push_back (str);
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
  bool is_valid = true;
  int rs = 0;
  while (std::getline (file, line))
    {
      auto parsed = parse_line (line);
      for (const auto &str : parsed)
        {
          bool abba_rs = find_rev_pair (str);
          if (abba_rs)
            {
              rs++;
              break;
            }
        }
    }
  std::cout << rs;
  file.close ();
  return 0;
}
