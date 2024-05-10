#include <algorithm>
#include <array>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

struct handbidpair
{
  int bid;
  std::string hand;
  handbidpair (int x, std::string y)
      : bid (x), hand (std::move (std::move (y)))
  {
  }
};

int
find_type (std::string &hand)
{
  std::map<char, int> char_map;
  for (char &i : hand)
    {
      if (char_map.count (i) != 0u)
        {
          char_map[i] += 1;
        }
      else
        {
          char_map[i] = 1;
        }
    }
  if (char_map.size () == 1)
    {
      return 6;
    }
  if (char_map.size () == 2)
    {
      for (const auto &[key, value] : char_map)
        {
          if (value == 4)
            {
              return 5;
            }
          else if (value == 2)
            {
              return 4;
            }
        }
    }
  else if (char_map.size () == 3)
    {
      for (const auto &[key, value] : char_map)
        {
          if (value == 3)
            {
              return 3;
            }
        }
      return 2;
    }
  else if (char_map.size () == 4)
    {
      return 1;
    }
  return 0;
}

bool
hand_sort (const struct handbidpair &first, const struct handbidpair &second)
{
  const std::map<char, int> lookup
      = { { '2', 1 },  { '3', 2 },  { '4', 3 }, { '5', 4 }, { '6', 5 },
          { '7', 6 },  { '8', 7 },  { '9', 8 }, { 'T', 9 }, { 'J', 10 },
          { 'Q', 11 }, { 'K', 12 }, { 'A', 13 } };
  for (int i = 0; i < first.hand.length (); i++)
    {
      if (lookup.at (first.hand[i]) > lookup.at (second.hand[i]))
        {
          return true;
        }
      if (lookup.at (first.hand[i]) < lookup.at (second.hand[i]))
        {
          return false;
        }
    }
  return false;
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
  std::array<std::vector<struct handbidpair>, 7> types;
  std::string line;
  while (std::getline (file, line))
    {
      std::string hand = line.substr (0, line.find (' '));
      std::string bid_str = line.substr ((line.find (' ')) + 1);
      int bid = 0;
      for (char &num : bid_str)
        {
          bid = (bid * 10) + (num - '0');
        }
      int type = find_type (hand);
      struct handbidpair pair
      {
        bid, hand
      };
      types[type].push_back (pair);
    }
  for (auto &type : types)
    {
      std::sort (type.begin (), type.end (), hand_sort);
    }
  int rs = 0;
  int total = 1;
  for (auto &type : types)
    {
      for (int j = type.size () - 1; j >= 0; j--)
        {
          // std::cout<<types[i][j].hand<<' '<<total<<' '<<i<<'\n';
          rs += type[j].bid * total;
          total++;
        }
    }
  std::cout << rs;
  return 0;
}
