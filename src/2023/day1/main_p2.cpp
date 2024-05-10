#include <array>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

struct member
{
  std::string str;
  int num;
};

std::array<struct member, 10> lookup{ { { "zero", 0 },
                                        { "one", 1 },
                                        { "two", 2 },
                                        { "three", 3 },
                                        { "four", 4 },
                                        { "five", 5 },
                                        { "six", 6 },
                                        { "seven", 7 },
                                        { "eight", 8 },
                                        { "nine", 9 } } };

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
  int rs = 0;
  std::string line;
  while (std::getline (file, line))
    {
      std::vector<int> line_rs;
      for (int i = 0; i < line.length (); i++)
        {
          if (std::isdigit (line[i]) != 0)
            {
              line_rs.push_back (line[i] - '0');
            }
          else
            {
              for (auto &j : lookup)
                {
                  int idx = line.find (j.str, i);
                  if (idx == i)
                    {
                      line_rs.push_back (j.num);
                      i += j.str.size () - 2;
                      break;
                    }
                }
            }
        }
      int total = line_rs[0] * 10 + line_rs.back ();
      // std::cout<<total<<'\n';
      rs += total;
    }
  std::cout << rs;
  file.close ();
  return 0;
}
