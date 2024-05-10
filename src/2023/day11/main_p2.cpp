#include <algorithm>
#include <cmath>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <numeric>
#include <string>
#include <vector>

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
  std::vector<std::string> universe;
  std::vector<std::pair<int, int> > galaxy_positions;
  for (int i = 0; std::getline (file >> std::ws, line); i++)
    {
      if (line.find ('#') == std::string::npos)
        {
          std::replace (line.begin (), line.end (), '.', '@');
        }
      else
        {
          for (int j = 0; j < line.size (); j++)
            {
              if (line[j] == '#')
                {
                  galaxy_positions.emplace_back (i, j);
                }
            }
        }
      universe.push_back (line);
    }
  for (int i = 0; i < universe[0].size (); i++)
    {
      std::string col;
      for (auto &j : universe)
        {
          col.push_back (j[i]);
        }
      if (col.find ('#') == std::string::npos)
        {
          for (auto &j : universe)
            {
              j[i] = '@';
            }
        }
    }
  std::vector<uint64_t> distances;
  for (int i = 0; i < galaxy_positions.size (); i++)
    {
      auto current_galaxy = galaxy_positions[i];
      for (int j = i + 1; j < galaxy_positions.size (); j++)
        {
          auto target_galaxy = galaxy_positions[j];
          int x_distance
              = std::abs (current_galaxy.first - target_galaxy.first);
          int y_distance = current_galaxy.second - target_galaxy.second;
          uint64_t rs = 0;
          for (int x_step = 0; x_step < x_distance; x_step++)
            {
              rs += (universe[current_galaxy.first + x_step]
                             [current_galaxy.second]
                     == '@')
                        ? 1000000
                        : 1;
            }
          if (y_distance < 0)
            {
              for (int y_step = 1; y_step <= -y_distance; y_step++)
                {
                  rs += (universe[current_galaxy.first + x_distance]
                                 [current_galaxy.second + y_step]
                         == '@')
                            ? 1000000
                            : 1;
                }
            }
          else
            {
              for (int y_step = 1; y_step <= y_distance; y_step++)
                {
                  rs += (universe[target_galaxy.first]
                                 [target_galaxy.second + y_step]
                         == '@')
                            ? 1000000
                            : 1;
                }
            }
          distances.push_back (rs);
          std::cout << "galaxy " << i + 1 << " to " << j + 1 << " is : " << rs
                    << '\n';
        }
    }
  for (auto x : distances)
    {
      std::cout << x << ' ';
    }
  std::cout << std::accumulate (distances.begin (), distances.end (), 0);
  return 0;
}
