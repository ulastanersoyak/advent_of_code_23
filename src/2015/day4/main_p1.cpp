#include <array>
#include <cstdint>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <openssl/md5.h>
#include <string>

std::string
md5 (const std::string &input)
{
  MD5_CTX context;
  MD5_Init (&context);
  MD5_Update (&context, input.c_str (), input.length ());

  unsigned char digest[MD5_DIGEST_LENGTH];
  MD5_Final (digest, &context);

  std::stringstream stream;
  for (int i = 0; i < MD5_DIGEST_LENGTH; ++i)
    stream << std::hex << std::setw (2) << std::setfill ('0')
           << static_cast<int> (digest[i]);

  return stream.str ();
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
  std::getline (file, line);
  for (uint64_t i = 0; i < INTMAX_MAX; i++)
    {
      std::string temp = md5 (line + std::to_string (i));
      bool found = true;
      for (int j = 0; j < 5; j++)
        {
          if (temp[j] != '0')
            {
              found = false;
              break;
            }
        }
      if (found)
        {
          std::cout << i << std::endl;
          break;
        }
    }
  file.close ();
  return 0;
}
