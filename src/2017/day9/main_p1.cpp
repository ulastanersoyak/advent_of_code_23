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
  std::string line;
  std::getline (file, line);
  file.close ();
  int rs = 0;
  bool inside_trash = false;
  bool skip_char = false;
  int depth = 0;
  for (char i : line)
    {
      if (inside_trash)
        {
          if (skip_char)
            {
              skip_char = false;
            }
          else if (i == '!')
            {
              skip_char = true;
            }
          else if (i == '>')
            {
              inside_trash = false;
            }
        }
      else
        {
          if (i == '{')
            {
              depth++;
            }
          else if (i == '}')
            {
              rs += depth;
              depth--;
            }
          else if (i == '<')
            {
              inside_trash = true;
            }
        }
    }
  std::cout << rs;
  return 0;
}
