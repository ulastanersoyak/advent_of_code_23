#include <fstream>
#include <iostream>
#include <iterator>
#include <map>
#include <string>

bool
does_have_repeating_char (const std::string &arg)
{
  int count = 0;
  std::map<std::string, int> lookup;
  for (int i = 0; i < arg.size (); i += 2)
    {
      std::string temp;
      temp.push_back (arg[i]);
      temp.push_back (arg[i + 1]);
      lookup[temp]++;
    }
  for (const auto &[key, value] : lookup)
    {
      if (value > 1)
        {
          return true;
        }
    }
  return false;
}

bool
does_have_three_vowels (const std::string &arg)
{
  for (int i = 2; i < arg.size (); i++)
    {
      if (arg[i] == arg[i - 2])
        {
          return true;
        }
    }
  return false;
}
bool
is_nice (const std::string &arg)
{
  bool result = true;
  result = result && does_have_three_vowels (arg);
  result = result && does_have_repeating_char (arg);
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
  int rs = 0;
  while (std::getline (file, line))
    {
      if (is_nice (line))
        {
          rs++;
        }
    }
  file.close ();
  std::cout << rs;
  return 0;
}
