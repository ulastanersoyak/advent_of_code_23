#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <utility>
#include <vector>

struct pos {
  int signature;
  int x;
  int y;
  std::pair<int, int> direction;
  pos() = default;
  pos(int x_, int y_, std::pair<int, int> direction_, int sign_)
      : x(x_), y(y_), direction(direction_), signature(sign_) {}
  void change_direction(const std::pair<int, int> &new_dir) {
    this->direction.first = new_dir.first;
    this->direction.second = new_dir.second;
  }
  void move() {
    this->x += direction.first;
    this->y += direction.second;
  }
};

struct mirror {
  int x;
  int y;
  std::pair<int, int> FROM;
  std::pair<int, int> TO;
  mirror(int x_, int y_, const std::pair<int, int> &FROM_,
         const std::pair<int, int> &TO_)
      : x(x_), y(y_), FROM(FROM_), TO(TO_) {}
  bool operator<(const mirror &other) const {
    return std::tie(x, y, FROM, TO) <
           std::tie(other.x, other.y, other.FROM, other.TO);
  }
};

std::pair<int, int> UP{-1, 0};
std::pair<int, int> DOWN{1, 0};
std::pair<int, int> LEFT{0, -1};
std::pair<int, int> RIGHT{0, 1};

int main(int argc, char **argv) {
  if (argc < 2) {
    std::cerr << "usage: " << argv[0] << " <filename>\n";
    return -1;
  }
  std::ifstream file{argv[1]};
  if (!file) {
    std::cerr << "failed to open file " << argv[1];
    return -1;
  }
  std::string line;
  std::vector<std::string> map;
  std::map<mirror, int> mirror_map;
  while (std::getline(file, line)) {
    map.push_back(line);
  }
  file.close();
  std::vector<pos> initial_beams;
  for (int i = 0; i < map.size(); i++) {
    int size = map.size();
    initial_beams.emplace_back(i, -1, RIGHT, 1);
    initial_beams.emplace_back(i, map[0].size(), LEFT, 1);
  }
  for (int i = 0; i < map[0].size(); i++) {
    int size = map[0].size();
    initial_beams.emplace_back(-1, i, DOWN, 1);
    initial_beams.emplace_back(map.size(), i, UP, 1);
  }
  // for (int i = 0; i < initial_beams.size(); i++) {
  //   std::cout << "beam " << i << " location: " << initial_beams[i].x << ' '
  //             << initial_beams[i].y << '\n';
  // }
  // return 0;
  std::vector<int> results;
  for (auto init_beam : initial_beams) {

    std::vector<pos> beams;
    beams.push_back(init_beam);
    std::map<std::pair<int, int>, int> visited_pos;
    while (!beams.empty()) {

      std::vector<pos> local_beams;
      for (auto &beam : beams) {
        beam.move();
        if (beam.x < 0 || beam.x >= map.size() || beam.y < 0 ||
            beam.y >= map[0].size()) {
          continue;
        }
        visited_pos[std::make_pair(beam.x, beam.y)] += 1;

        if (map[beam.x][beam.y] == '/') {
          mirror cur_mir{
              beam.x, beam.y, beam.direction,
              std::make_pair(-beam.direction.second, -beam.direction.first)};
          if (mirror_map[cur_mir] >= 1) {
            beam.signature = 0;
          }
          mirror_map[cur_mir] += 1;

          beam.change_direction(
              std::make_pair(-beam.direction.second, -beam.direction.first));

        } else if (map[beam.x][beam.y] == '\\') {
          mirror cur_mir{
              beam.x, beam.y, beam.direction,
              std::make_pair(beam.direction.second, beam.direction.first)};

          if (mirror_map[cur_mir] >= 1) {
            beam.signature = 0;
          }
          mirror_map[cur_mir] += 1;

          beam.change_direction(
              std::make_pair(beam.direction.second, beam.direction.first));

        } else if (map[beam.x][beam.y] == '|') {

          if (beam.direction == UP || beam.direction == DOWN) {
            continue;
          } else {
            beam.change_direction(
                std::make_pair(beam.direction.second, beam.direction.first));
            local_beams.emplace_back(
                beam.x, beam.y,
                std::make_pair(-beam.direction.first, -beam.direction.second),
                1);
          }

        } else if (map[beam.x][beam.y] == '-') {

          if (beam.direction == RIGHT || beam.direction == LEFT) {
            continue;
          } else {
            beam.change_direction(
                std::make_pair(beam.direction.second, beam.direction.first));
            local_beams.emplace_back(
                beam.x, beam.y,
                std::make_pair(-beam.direction.first, -beam.direction.second),
                1);
          }
        }
      }
      beams.erase(std::remove_if(beams.begin(), beams.end(),
                                 [&map](const pos &beam) {
                                   return beam.x < 0 || beam.x >= map.size() ||
                                          beam.y < 0 ||
                                          beam.y >= map[0].size() ||
                                          beam.signature == 0;
                                 }),
                  beams.end());

      for (const auto &new_beams : local_beams) {
        beams.push_back(new_beams);
      }
      local_beams.clear();
    }
    results.push_back(visited_pos.size());
    for (auto &[key, value] : mirror_map) {
      value = 0;
    }
  }
  for (auto x : results) {
    std::cout << x << ' ';
  }
  auto rs = std::max_element(results.begin(), results.end());
  std::cout << *rs;
  return 0;
}
