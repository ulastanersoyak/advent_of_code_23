#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

struct disc
{
  int weight;
  std::string name;
  std::vector<std::string> up;
};

struct disc
parse_line (const std::string &arg)
{
  size_t open_paranthesis = arg.find ('(');
  std::string name = arg.substr (0, arg.find (' '));
  int weight = std::stoi (arg.substr (open_paranthesis + 1,
                                      arg.find (')') - open_paranthesis - 1));
  size_t arrow = arg.find ("->");
  std::vector<std::string> elements;
  if (arrow != std::string::npos)
    {
      std::string right = arg.substr (arrow + 2);
      std::istringstream iss (right);
      std::string element;
      while (std::getline (iss, element, ','))
        {
          element.erase (
              element.begin (),
              std::find_if (element.begin (), element.end (),
                            [] (int ch) { return std::isspace (ch) == 0; }));
          element.erase (
              std::find_if (element.rbegin (), element.rend (),
                            [] (int ch) { return std::isspace (ch) == 0; })
                  .base (),
              element.end ());
          elements.push_back (element);
        }
    }
  return disc{ weight, name, elements };
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
  std::vector<disc> all_discs;
  while (std::getline (file, line))
    {
      all_discs.emplace_back (parse_line (line));
    }
  file.close ();
  std::map<std::string, int> hashmap;
  for (const auto &disc : all_discs)
    {
      hashmap[disc.name] += 1;
      for (const auto &i : disc.up)
        {
          hashmap[i] += 1;
        }
    }
  for (const auto &[key, value] : hashmap)
    {
      if (value == 1)
        {
          std::cout << key << '\n';
        }
    }
  return 0;
}
