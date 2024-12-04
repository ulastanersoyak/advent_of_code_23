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
  std::vector<std::vector<int64_t> > parsed_file{};

  std::vector<std::int64_t> line_nums{};

  for (const auto &line : std::ranges::views::split (contents, '\n'))
    {
      if (line.empty ())
        {
          break;
        }

      for (const auto &num : std::ranges::views::split (line, ' '))
        {
          line_nums.push_back (std::stoul (num.data ()));
        }
      parsed_file.push_back (line_nums);
      line_nums.clear ();
    }
  return parsed_file;
}

int
main (int argc, char **argv)
{
  if (argc < 2)
    {
      std::println ("usage: {} <input_path>", argv[0]);
      return EXIT_FAILURE;
    }

  std::ifstream file (argv[1]);
  std::stringstream buffer;
  buffer << file.rdbuf ();
  const std::string content = buffer.str ();
  const auto args = parse_args (content);
  std::int64_t rs{ 0 };
  for (const auto &line_vec : args)
    {
      char state = line_vec.at (0) > line_vec.at (1) ? 'd' : 'i';
      bool is_ok = true;
      for (std::size_t i = 1; i < line_vec.size (); ++i)
        {

          char curr_state = line_vec.at (i - 1) > line_vec.at (i) ? 'd' : 'i';
          const auto diff = std::abs (line_vec.at (i - 1) - line_vec.at (i));

          if (curr_state != state || !(diff <= 3 && (diff > 0)))
            {
              is_ok = false;
              break;
            }
        }
      if (is_ok)
        {
          rs++;
        }
    }
  std::println ("{}", rs);
}
