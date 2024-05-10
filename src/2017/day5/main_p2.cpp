#include <fstream>
#include <iostream>
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
  std::vector<int> instructions;
  while (std::getline (file, line))
    {
      instructions.push_back (std::stoi (line));
    }
  file.close ();
  int current = 0;
  int step = 0;
  while (1)
    {
      if (current < 0 || current >= instructions.size ())
        {
          break;
        }
      step++;
      int offset = instructions[current];
      if (offset >= 3)
        {
          instructions[current]--;
        }
      else
        {
          instructions[current]++;
        }
      current += offset;
    }
  std::cout << step;
  return 0;
}
