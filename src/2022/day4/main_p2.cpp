#include <fstream>
#include <iostream>
#include <string>
#include <utility>

std::pair<int, int>
parse_pair (const std::string &arg)
{
  int i = 0;
  int first = 0;
  for (; arg[i] != '-'; i++)
    {
      first = (first * 10) + (arg[i] - '0');
    }
  int second = 0;
  for (int j = i + 1; j < arg.size (); j++)
    {
      second = (second * 10) + (arg[j] - '0');
    }
  return std::pair<int, int>{ first, second };
}

std::pair<std::pair<int, int>, std::pair<int, int> >
parse_line (const std::string &arg)
{
  auto first_pair = arg.substr (0, arg.find (','));
  auto second_pair = arg.substr (arg.find (',') + 1, arg.size ());
  return std::pair<std::pair<int, int>, std::pair<int, int> >{
    parse_pair (first_pair), parse_pair (second_pair)
  };
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
      auto pairs = parse_line (line);
      if (!((pairs.first.first < pairs.second.first
             && pairs.first.second < pairs.second.first)
            || (pairs.first.first > pairs.second.second
                && pairs.first.second > pairs.second.second)
            || (pairs.second.first < pairs.first.first
                && pairs.second.second < pairs.first.first)
            || (pairs.second.first > pairs.first.second
                && pairs.second.second > pairs.first.second)))
        {
          rs++;
        }
    }

  std::cout << rs;
  return 0;
}
