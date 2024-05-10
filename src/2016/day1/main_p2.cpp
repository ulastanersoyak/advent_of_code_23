#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<std::pair<char, int> >
parse_data (const std::vector<std::string> &data)
{
  std::vector<std::pair<char, int> > parsed_data;
  for (const auto element : data)
    {
      parsed_data.emplace_back (
          element[1], std::stoi (element.substr (2, element.size ())));
    }
  return parsed_data;
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
  std::vector<std::string> data;
  while (file.good ())
    {
      std::string line;
      std::getline (file, line, ',');
      data.push_back (line);
    }
  file.close ();
  auto parsed_data = parse_data (std::move (data));
  std::pair<int, int> current_pos{ 0, 0 };
  bool is_vertical = true;
  char prev_dir = 0;
  for (const auto &[direction, distance] : parsed_data)
    {
      std::cout << current_pos.first << ' ' << current_pos.second << '\n';
      if (is_vertical)
        {
          int dir = direction == 'R' ? 1 : -1;
          current_pos.first += distance * dir;
        }
      else
        {
          int dir = direction == prev_dir ? 1 : -1;
          current_pos.second += distance * dir;
        }
      is_vertical = is_vertical ^ 1;
      prev_dir = direction;
    }
  std::cout << std::abs (current_pos.first) + std::abs (current_pos.second);
  return 0;
}
