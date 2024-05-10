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
  std::string num;
  std::vector<int> opcode;
  while (std::getline (file, num, ','))
    {
      opcode.push_back (std::stoi (num));
    }
  file.close ();
  opcode[1] = 12;
  opcode[2] = 2;
  for (int i = 0; i < opcode.size (); i += 4)
    {
      if (opcode[i] == 99)
        {
          break;
        }
      if (opcode[i] == 1)
        {
          opcode[opcode[i + 3]]
              = opcode[opcode[i + 1]] + opcode[opcode[i + 2]];
        }
      else if (opcode[i] == 2)
        {
          opcode[opcode[i + 3]]
              = opcode[opcode[i + 1]] * opcode[opcode[i + 2]];
        }
    }
  std::cout << opcode[0];
  return 0;
}
