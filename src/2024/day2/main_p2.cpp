#include <cstdlib>
#include <fstream>
#include <print>
#include <ranges>
#include <sstream>
#include <string>
#include <string_view>
#include <vector>

std::vector<std::vector<int64_t> >
parse_args (std::string_view contents)
{
  std::vector<std::vector<int64_t> > parsed_file;
  std::vector<int64_t> line_nums;

  for (const auto &line : std::ranges::views::split (contents, '\n'))
    {
      if (line.empty ())
        {
          break;
        }
      line_nums.clear ();
      for (const auto &num : std::ranges::views::split (line, ' '))
        {
          line_nums.push_back (
              std::stoul (std::string (num.begin (), num.end ())));
        }
      parsed_file.push_back (line_nums);
    }
  return parsed_file;
}

bool
is_naturally_safe (const std::vector<int64_t> &sequence)
{
  if (sequence.size () < 2)
    return true;

  bool should_increase = sequence[1] > sequence[0];

  for (size_t i = 1; i < sequence.size (); ++i)
    {
      int64_t diff = sequence[i] - sequence[i - 1];

      if (should_increase && (diff <= 0 || diff > 3))
        return false;
      if (!should_increase && (diff >= 0 || diff < -3))
        return false;
    }
  return true;
}

bool
is_safe_with_dampener (const std::vector<int64_t> &sequence)
{
  if (sequence.size () < 3)
    return true;

  for (size_t skip = 0; skip < sequence.size (); ++skip)
    {
      std::vector<int64_t> modified;
      modified.reserve (sequence.size () - 1);

      for (size_t i = 0; i < sequence.size (); ++i)
        {
          if (i != skip)
            {
              modified.push_back (sequence[i]);
            }
        }

      if (is_naturally_safe (modified))
        {
          return true;
        }
    }
  return false;
}

int
main (int argc, char **argv)
{
  if (argc < 2)
    {
      std::println ("Usage: {} <input_path>", argv[0]);
      return EXIT_FAILURE;
    }

  std::ifstream file (argv[1]);
  std::stringstream buffer;
  buffer << file.rdbuf ();
  const auto args = parse_args (buffer.str ());

  int64_t safe_count = 0;
  for (const auto &sequence : args)
    {
      if (is_naturally_safe (sequence) || is_safe_with_dampener (sequence))
        {
          safe_count++;
        }
    }

  std::println ("{}", safe_count);
  return EXIT_SUCCESS;
}
