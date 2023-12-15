#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

struct position {
  int x;
  int y;
  position() = default;
  constexpr position(int x_, int y_) : x(x_), y(y_) {}
  [[nodiscard]] bool operator==(const position &other) const {
    return ((this->x == other.x) && (this->y == other.y));
  }
  [[nodiscard]] position operator-() const {
    return position(-this->x, -this->y);
  }
  [[nodiscard]] position operator+(const position &other) const {
    return position(this->x + other.x, this->y + other.y);
  }
};

position NORTH(1, 0);
position SOUTH(-1, 0);
position WEST(0, 1);
position EAST(0, -1);

std::map<char, std::pair<position, position>> lookup{
    {'|', std::pair<position, position>{NORTH, SOUTH}},
    {'-', std::pair<position, position>{WEST, EAST}},
    {'F', std::pair<position, position>{SOUTH, EAST}},
    {'7', std::pair<position, position>{SOUTH, WEST}},
    {'J', std::pair<position, position>{NORTH, WEST}},
    {'L', std::pair<position, position>{NORTH, EAST}}};

std::vector<char> get_adj_tiles(const std::vector<std::string> &tilemap,
                                const position &start) {
  std::vector<char> res;
  res.push_back(tilemap[start.x - 1][start.y]);
  res.push_back(tilemap[start.x + 1][start.y]);
  res.push_back(tilemap[start.x][start.y - 1]);
  res.push_back(tilemap[start.x][start.y + 1]);
  return res;
}

char get_start_tile(const std::vector<char> &adjacent_tiles) {
  std::vector<std::pair<position, position>> directions;
  for (const auto &ch : adjacent_tiles) {
    directions.push_back(lookup[ch]);
  }
  std::vector<position> res;
  if (directions[0].first == SOUTH || directions[0].second == SOUTH) {
    res.push_back(NORTH);
  }
  if (directions[1].first == NORTH || directions[1].second == NORTH) {
    res.push_back(SOUTH);
  }
  if (directions[2].first == EAST || directions[0].second == EAST) {
    res.push_back(WEST);
  }
  if (directions[3].first == WEST || directions[0].second == WEST) {
    res.push_back(EAST);
  }
  std::pair<position, position> start_directions;
  start_directions.first = res.back();
  res.pop_back();
  start_directions.second = res.back();
  for (const auto &[key, value] : lookup) {
    if ((start_directions.first == value.first &&
         start_directions.second == value.second) ||
        (start_directions.first == value.second &&
         start_directions.second == value.first)) {
      return key;
    }
  }
  return 0;
}

struct rat {
  position prev;
  position current;
  int step;
  char curchar;
  rat() = default;
  rat(position prev_, position current_, int step_, char curchar_)
      : prev(prev_), current(current_), step(step_), curchar(curchar_) {}
};

int traverse(const std::vector<std::string> &tilemap, rat &player) {
  while (player.curchar != 'S') {
    position next_direction = (-player.prev == lookup[player.curchar].first)
                                  ? lookup[player.curchar].second
                                  : lookup[player.curchar].first;
    player.current = player.current + (-next_direction);
    player.prev = next_direction;
    player.curchar = tilemap[player.current.x][player.current.y];
    player.step++;
  }
  return player.step;
}

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
  std::vector<std::string> tilemap;
  position start;
  for (int i = 0; std::getline(file >> std::ws, line); i++) {
    if (!(line.find('S') == std::string::npos)) {
      start.x = i;
      start.y = line.find('S');
    }
    tilemap.push_back(line);
  }
  auto adj_tiles = get_adj_tiles(tilemap, start);
  char start_tile = get_start_tile(adj_tiles);
  rat player(lookup[start_tile].first, start + (-lookup[start_tile].first), 1,
             tilemap[start.x + (-lookup[start_tile].first.x)]
                    [start.y + (-lookup[start_tile].first.y)]);
  auto rs = traverse(tilemap, player);
  std::cout << rs / 2;
  return 0;
}
