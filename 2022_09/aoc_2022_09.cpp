#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_set>

#ifdef DEBUG
#define DEBUG_MSG(str) do { std::cout << str << std::endl; } while( false )
#else
#define DEBUG_MSG(str) do { } while ( false )
#endif


auto get_lines() -> std::vector<std::string> {
  std::ifstream input_file("input.txt");

  if (!input_file.is_open())
    std::cout << "Error opening file" << std::endl;

  std::vector<std::string> lines;
  std::string line;
  while (std::getline(input_file, line))
    lines.push_back(line);

  input_file.close();
  return lines;
}

class Timer {
public:
  Timer(){};
  auto start() -> void { m_start = std::chrono::high_resolution_clock::now(); }
  auto stop() -> void { m_end = std::chrono::high_resolution_clock::now(); }

  auto print_all() -> void {
    print_milliseconds();
    print_microseconds();
    print_nanoseconds();
  }

  auto print_milliseconds() -> void {
    print<std::chrono::milliseconds>();
    std::cout << "ms\n";
  }

  auto print_microseconds() -> void {
    print<std::chrono::microseconds>();
    std::cout << "us\n";
  }

  auto print_nanoseconds() -> void {
    print<std::chrono::nanoseconds>();
    std::cout << "ns\n";
  }

private:
  std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
  std::chrono::time_point<std::chrono::high_resolution_clock> m_end;

  template <typename T>
  auto print() -> void {
    auto duration = std::chrono::duration_cast<T>(m_end - m_start);
    std::cout << "Time taken: " << duration.count();
  }

};

struct Move {
  char direction;
  int distance;
};

using MoveList = std::vector<Move>;

auto generate_moves(const std::vector<std::string>& lines) -> MoveList {
  MoveList moves;
  for (const auto& line : lines) {
    Move move;
    move.direction = line[0];
    move.distance = std::stoi(line.substr(1));
    moves.push_back(move);
  }
  return moves;
}

auto print_moves(const MoveList& movelist) {
  for (const auto& move : movelist)
    std::cout << move.direction << ' ' << move.distance << std::endl;
}

struct Position {
  int x;
  int y;

  bool operator==(const Position& other) const {
    return x == other.x && y == other.y;
  }
};

// Guess I need this bullshit for the unordered_set shit
struct PositionHash {
public:
  size_t operator()(const Position p) const {
    return std::hash<uint32_t>()(p.x) ^ std::hash<uint32_t>()(p.y);
  }
};

using PositionSet = std::unordered_set<Position, PositionHash>;

auto print_all_positions_on_grid(const PositionSet& positions_visited) {
  
  // copy all positions visited to a vector so we can actually use it lol
  std::vector<Position> positions_visited_vector;
  positions_visited_vector.reserve(positions_visited.size());
  std::copy(positions_visited.begin(), positions_visited.end(), std::back_inserter(positions_visited_vector));
  
  auto lowest_position_x = std::min_element(positions_visited.begin(),
                                            positions_visited.end(),
                                            [](const Position& a, const Position& b) { return a.x < b.x; })->x;
  
  auto lowest_position_y = std::min_element(positions_visited.begin(),
                                            positions_visited.end(),
                                            [](const Position& a, const Position& b) { return a.y < b.y; })->y;

  // Make everything positive to make them easily printable
  // We don't actually care about their positions here, just the relative positions
  for (auto& position : positions_visited_vector) {
    position.x += abs(lowest_position_x);
    position.y += abs(lowest_position_y);
  }

  auto max_position_x = std::max_element(positions_visited_vector.begin(),
                                         positions_visited_vector.end(),
                                         [](const Position& a, const Position& b) { return a.x < b.x; })->x;
  auto max_position_y = std::max_element(positions_visited_vector.begin(),
                                         positions_visited_vector.end(),
                                         [](const Position& a, const Position& b) { return a.y < b.y; })->y;

  // Inefficient way to print and find position for the coordinates.
  // But it works fast enough for debugging.
  for (int y = max_position_y; y >= 0 ; --y) {
    for (int x = 0; x <= max_position_x + 1; ++x) {

      auto position = std::find_if(positions_visited_vector.begin(),
                                   positions_visited_vector.end(),
                                   [x, y](const Position& p) { return p.x == x && p.y == y; });

      if (x == 0 && y == 0)
        std::cout << "S";
      else if (position != positions_visited_vector.end())
        std::cout << "#";
      else
        std::cout << ".";
    }
    std::cout << std::endl;
  }
}

auto print_head_and_tail_on_grid(const Position& head_position, const Position& tail_position) {
  auto grid_max_x = 6;
  auto grid_max_y = 5;

  for (int y = grid_max_y - 1; y >= 0; --y) {
    for (int x = 0; x < grid_max_x; ++x) {
      if (x == 0 && y == 0)
        std::cout << "S";
      else if (x == head_position.x && y == head_position.y)
        std::cout << "H";
      else if (x == tail_position.x && y == tail_position.y)
        std::cout << "T";
      else
        std::cout << ".";
    }
    std::cout << std::endl;
  }
}

auto update_position_of_tail_based_on_head(const Position& head_position, Position& tail_position) {
  auto xdiff = head_position.x - tail_position.x;
  auto ydiff = head_position.y - tail_position.y;

  if (abs(xdiff) <= 1 && abs(ydiff) <= 1) {
    // Do nothing
    DEBUG_MSG("Move of tail: Touching\n");
  }
  else if (abs(xdiff) == 2 && ydiff == 0) {
    tail_position = {tail_position.x + xdiff / 2, tail_position.y};
    DEBUG_MSG("Moveof tail: in straight line x-wise\n");
  }
  else if (xdiff == 0 && abs(ydiff) == 2) {
    tail_position = {tail_position.x, tail_position.y + ydiff / 2};
    DEBUG_MSG("Move of tail: in straight line y-wise\n");
  }
  else {
    tail_position = {tail_position.x + xdiff / abs(xdiff), tail_position.y + ydiff / abs(ydiff)};
    DEBUG_MSG("Move of tail: diagonal\n");
  }
}

auto part_one(const std::vector<std::string>& lines) -> int {
  auto moves = generate_moves(lines);

  Position head_position = {0, 0};
  Position tail_position = {0, 0};
  PositionSet positions_visited;
  positions_visited.insert(head_position);

  for (auto const& move : moves) {
    for (int i = 0; i < move.distance; i++) {
      auto snapshot_head_position = head_position;
      auto snapshot_tail_position = tail_position;
      switch (move.direction) {
        case 'U':
          head_position = {head_position.x, head_position.y + 1};
        break;
        case 'D':
          head_position = {head_position.x, head_position.y - 1};
        break;
        case 'L':
          head_position = {head_position.x - 1, head_position.y};
        break;
        case 'R':
          head_position = {head_position.x + 1, head_position.y};
        break;
        default:
          std::cout << "Invalid direction: " << move.direction << std::endl;
        break;
      }

      update_position_of_tail_based_on_head(head_position, tail_position);

      positions_visited.insert(tail_position);
    }
  }

  return positions_visited.size();
}

auto part_two(const std::vector<std::string>& lines) -> int {
  auto moves = generate_moves(lines);

  Position head_position = {0, 0};
  const static auto tail_length = 9;
  std::vector <Position> tail_positions(tail_length, {0, 0});

  PositionSet positions_visited;
  for (auto const& move : moves) {
    for (int i = 0; i < move.distance; i++) {
      auto snapshot_head_position = head_position;
      switch (move.direction) {
        case 'U':
          head_position = {head_position.x, head_position.y + 1};
        break;
        case 'D':
          head_position = {head_position.x, head_position.y - 1};
        break;
        case 'L':
          head_position = {head_position.x - 1, head_position.y};
        break;
        case 'R':
          head_position = {head_position.x + 1, head_position.y};
        break;
        default:
        break;
      }
      
      update_position_of_tail_based_on_head(head_position, tail_positions[0]);
      for (int i = 1; i < tail_positions.size(); ++i) {
        auto& tail_before = tail_positions[i - 1];
        auto& current_tail = tail_positions[i];
        update_position_of_tail_based_on_head(tail_before, current_tail);
      }
      
      positions_visited.insert(tail_positions[tail_length - 1]);
    }
  }

  return positions_visited.size();
}


int main () {
  auto lines = get_lines();

  Timer part_one_timer;
  part_one_timer.start();
  auto lines = get_lines();
  auto unique_positions_visited = part_one(lines);
  part_one_timer.stop();

  Timer part_two_timer;
  part_two_timer.start();
  auto lines2 = get_lines();
  auto unique_positions_visited_part_two = part_two(lines2);
  part_two_timer.stop();

  std::cout << "Part one: Unique positions visited: " << unique_positions_visited << std::endl;
  part_one_timer.print_all();
  
  std::cout << "Part two: Unique positions visited: " << unique_positions_visited_part_two << std::endl;
  part_two_timer.print_all();

}