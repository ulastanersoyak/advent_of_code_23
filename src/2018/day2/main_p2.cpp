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
  std::vector<std::string> all_ids;
  while (std::getline (file, line))
    {
      all_ids.push_back (line);
    }
  file.close ();
  for (int i = 0; i < all_ids.size (); i++)
    {
      for (int j = i + 1; j < all_ids.size (); j++)
        {
          int diff = 0;
          if (all_ids[i].size () == all_ids[j].size ())
            {
              for (int k = 0; k < all_ids[i].size (); k++)
                {
                  if (all_ids[i][k] != all_ids[j][k])
                    {
                      diff++;
                    }
                }
            }
          if (diff == 1)
            {
              for (int k = 0; k < all_ids[j].size (); k++)
                {
                  if (all_ids[i][k] == all_ids[j][k])
                    {
                      std::cout << all_ids[i][k];
                    }
                }
            }
        }
    }
  return 0;
}
