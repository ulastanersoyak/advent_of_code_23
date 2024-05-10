#include <fstream>
#include <iostream>
#include <string>

struct submarine
{
  int x;
  int y;
};

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
  submarine sub{ 0, 0 };
  while (std::getline (file, line))
    {
      char command = line[0];
      int dist = std::stoi (line.substr (line.find (' ') + 1));
      if (command == 'f')
        {
          sub.x += dist;
        }
      else if (command == 'd')
        {
          sub.y += dist;
        }
      else if (command == 'u')
        {
          sub.y -= dist;
        }
    }
  file.close ();
  std::cout << sub.x * sub.y;
  return 0;
}
