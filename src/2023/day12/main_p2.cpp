#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

std::vector<int>
stoiv (const std::string &arg)
{
  std::vector<int> rs;
  int local = 0;
  for (const auto &ch : arg)
    {
      if (ch == ',')
        {
          rs.push_back (local);
          local = 0;
          continue;
        }
      local = (local * 10) + (ch - '0');
    }
  rs.push_back (local);
  return rs;
}

bool
check_seq (const std::string &seq, const std::vector<int> &gear_count)
{
  if (seq.find ('?') != std::string::npos)
    {
      return false;
    }
  int seq_size = 0;
  std::vector<int> gear_seq;
  for (const auto ch : seq)
    {
      if (ch == '#')
        {
          seq_size++;
        }
      else
        {
          if (seq_size > 0)
            {
              gear_seq.push_back (seq_size);
              seq_size = 0;
            }
        }
    }
  if (seq_size > 0)
    {

      gear_seq.push_back (seq_size);
    }
  if (gear_seq.size () != gear_count.size ())
    {
      return false;
    }
  for (int i = 0; i < gear_seq.size (); i++)
    {
      if (gear_seq[i] != gear_count[i])
        {
          return false;
        }
    }
  return true;
}

int
all_poss (std::string gears, const std::vector<int> &seq, uint64_t &cum_res)
{
  if (gears.find ('?') != std::string::npos)
    {
      int qmloc = gears.find ('?');
      gears[qmloc] = '#';
      all_poss (gears, seq, cum_res);
      gears[qmloc] = '.';
      all_poss (gears, seq, cum_res);
    }
  else
    {
      bool rs = check_seq (gears, seq);
      if (rs)
        {
          cum_res += 1;
        }
    }
  return cum_res;
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
  uint64_t x = 0;
  while (std::getline (file, line))
    {
      auto gears = line.substr (0, line.find (' '));
      gears = gears + '?' + gears + '?' + gears + '?' + gears + '?' + gears;
      auto gear_seq = stoiv (
          line.substr (line.find (' ') + 1, line.size () - line.find (' ')));
      uint64_t rs = 0;
      auto copy = gear_seq;
      for (int i = 0; i < 4; i++)
        {
          for (auto x : copy)
            {
              gear_seq.push_back (x);
            }
        }
      all_poss (gears, gear_seq, rs);
      x += rs;
    }
  std::cout << x;
  return 0;
}
