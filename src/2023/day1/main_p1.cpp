#include <cctype>
#include <fstream>
#include <iostream>
#include <string>

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
  int rs = 0;
  std::string line;
  while (std::getline (file, line))
    {
      int n1 = -1;
      int n2 = -1;
      for (char i : line)
        {
          if (std::isdigit (i) != 0)
            {
              if (n1 == -1 && n2 == -1)
                {
                  n1 = i - '0';
                  n2 = i - '0';
                }
              else
                {
                  n2 = i - '0';
                }
            }
        }
      rs += n1 * 10 + n2;
    }
  std::cout << rs;
  file.close ();
  return 0;
}
