#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

uint64_t
to_num (std::string &line)
{
  std::vector<int> rs;
  line = line.substr (line.find (':') + 1);
  int num = 0;
  for (char i : line)
    {
      if (std::isdigit (i) != 0)
        {
          num = (num * 10) + (i - '0');
        }
      else if (num > 0)
        {
          rs.push_back (num);
          num = 0;
        }
    }
  if (num > 0)
    {
      rs.push_back (num);
      num = 0;
    }
  int result = 0;
  for (int num : rs)
    {
      result = result * 100 + num;
    }
  return result;
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
  std::getline (file, line);
  uint64_t time = to_num (line);
  std::getline (file, line);
  uint64_t distance = to_num (line);
  std::vector<uint64_t> results;
  std::cout << time << '\n';
  int64_t rs = 0;
  int64_t fd = 0;
  int64_t bd = 0;
  for (int64_t i = 0, j = time;; i++, j--)
    {
      if ((fd == 0) && (time - i) * i > distance)
        {
          fd = i;
        }
      if ((bd == 0) && (time - j) * j > distance)
        {
          bd = j;
        }
      if ((bd != 0) && (fd != 0))
        {
          break;
        }
    }
  rs = bd - fd;
  rs = (rs < 0) ? rs * -1 : rs;
  std::cout << ++rs;
  return 0;
}
