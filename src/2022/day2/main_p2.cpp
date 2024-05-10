#include <fstream>
#include <iostream>
#include <map>
#include <string>

#define WIN 6
#define LOSE 0
#define DRAW 3

char
get_mov (char opp_mov, char match_state)
{
  if (match_state == 'Y')
    {
      return opp_mov;
    }
  if (match_state == 'X')
    {
      if (opp_mov == 'R')
        {
          return 'S';
        }
      else if (opp_mov == 'P')
        {
          return 'R';
        }
      else
        {
          return 'P';
        }
    }
  else
    {
      if (opp_mov == 'R')
        {
          return 'P';
        }
      else if (opp_mov == 'P')
        {
          return 'S';
        }
      else
        {
          return 'R';
        }
    }
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
  std::map<char, char> move_lookup
      = { { 'A', 'R' }, { 'B', 'P' }, { 'C', 'S' } };
  std::map<char, int> stat_lookup = { { 'X', 0 }, { 'Y', 3 }, { 'Z', 6 } };
  std::map<char, int> score_lookup = { { 'R', 1 }, { 'P', 2 }, { 'S', 3 } };
  std::string line;
  int total_rs = 0;
  while (std::getline (file, line))
    {
      char mm = get_mov (move_lookup[line[0]], line[2]);
      total_rs += stat_lookup[line[2]] + score_lookup[mm];
    }
  std::cout << total_rs;
  return 0;
}
