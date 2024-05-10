#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

std::vector<int64_t>
parse_line (const std::string &str)
{
  std::vector<int64_t> rs;
  int num = 0;
  bool is_negative = false;
  for (const auto &ch : str)
    {
      if (ch == ' ' || ch == '\n')
        {
          if (is_negative)
            {
              num *= -1;
              is_negative = false;
            }
          rs.push_back (num);
          num = 0;
          continue;
        }
      if (ch == '-')
        {
          is_negative = true;
          continue;
        }
      num = ((num * 10) + (ch - '0'));
    }
  if (num != 0)
    {
      rs.push_back (num);
    }
  return rs;
}

std::vector<int64_t>
get_diff (const std::vector<int64_t> &arg)
{
  std::vector<int64_t> rs;
  rs.reserve (arg.size () - 1);
  for (int i = 0; i < arg.size () - 1; i++)
    {
      rs.push_back (std::abs (arg[i] - arg[i + 1]));
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
  uint64_t rs = 0;
  while (std::getline (file, line))
    {
      auto line_nums = parse_line (line);
      int dif = -1;
      std::vector<int64_t> line_rs;
      line_rs.push_back (line_nums.back ());
      while (dif != 0)
        {
          line_nums = get_diff (line_nums);
          dif = std::accumulate (line_nums.begin (), line_nums.end (), 0);
          if ((dif != 0) && (!line_nums.empty () != 0u))
            {
              line_rs.push_back (line_nums.back ());
            }
        }
      rs += std::accumulate (line_rs.begin (), line_rs.end (), 0);
    }
  std::cout << rs;
  return 0;
}
