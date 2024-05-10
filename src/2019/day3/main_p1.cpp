#include <array>
#include <cstdint>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

std::map<std::array<int, 2>, int>
get_points (const std::vector<std::pair<char, int> > &directions)
{
  std::map<std::array<int, 2>, int> table;
  std::array<int, 2> current_pos{ 0, 0 };
  for (const auto &direction : directions)
    {
      int idx = (direction.first == 'R' || direction.first == 'L') ? 0 : 1;
      int step = (direction.first == 'R' || direction.first == 'U') ? 1 : -1;
      for (int i = 0; i < direction.second; i++)
        {
          current_pos[idx] += step;
          if (table.count (current_pos) == 0u)
            {
              table[current_pos] += 1;
            }
        }
    }
  return table;
}

std::vector<std::pair<char, int> >
parse_line (const std::string &arg)
{
  std::istringstream ss (arg);
  std::vector<std::pair<char, int> > result;
  std::string token;

  while (std::getline (ss, token, ','))
    {
      char prefix = token[0];
      int value = std::stoi (token.substr (1));
      result.emplace_back (prefix, value);
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
  std::vector<std::map<std::array<int, 2>, int> > points_vec;
  while (std::getline (file, line))
    {
      auto directions = parse_line (line);
      points_vec.push_back (get_points (directions));
    }
  file.close ();
  std::vector<std::array<int, 2> > common_points;
  for (const auto &point : points_vec[0])
    {
      if (points_vec[1].count (point.first) != 0u)
        {
          common_points.push_back (point.first);
        }
    }
  int min = INT32_MAX;
  for (const auto &common : common_points)
    {
      auto distance = std::abs (common[0]) + std::abs (common[1]);
      if (distance < min)
        {
          min = distance;
        }
    }
  std::cout << min;
  return 0;
}
