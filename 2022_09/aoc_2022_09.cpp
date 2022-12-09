#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <unordered_set>
#include <array>

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

auto generate_moves(const std::vector<std::string>& lines) -> std::vector<Move> {
  std::vector<Move> moves;
  for (const auto& line : lines) {
    Move move;
    move.direction = line[0];
    move.distance = std::stoi(line.substr(1));
    moves.push_back(move);
  }
  return moves;
}

struct Position {
  int x = 0;
  int y = 0;

  bool operator==(const Position& other) const {
    return x == other.x && y == other.y;
  }

  auto operator-(const Position& other) const -> Position {
    return {x - other.x, y - other.y};
  }
};

// Guess I need this bullshit for the unordered_set shit
struct PositionHash {
public:
  size_t operator()(const Position p) const {
    return std::hash<uint32_t>()(p.x) ^ std::hash<uint32_t>()(p.y);
  }
};

inline auto signof(int x) -> int { return (x > 0) - (x < 0); }

auto both(const std::vector<std::string>& lines) -> std::pair<std::size_t, std::size_t> {
  auto moves = generate_moves(lines);

  std::array<Position, 10> knots;
  std::unordered_set<Position, PositionHash> positions_visited_p1;
  std::unordered_set<Position, PositionHash> positions_visited_p2;

  for (auto const& move : moves) {
    for (int i = 0; i < move.distance; i++) {
      switch (move.direction) {
        case 'U': knots[0].y += 1; break;
        case 'D': knots[0].y -= 1; break;
        case 'L': knots[0].x -= 1; break;
        case 'R': knots[0].x += 1; break;
      }
      
      for (int i = 1; i < knots.size(); ++i) {
        auto& head = knots[i - 1];
        auto& tail = knots[i];
        Position diff = head - tail;

        // We want to move in the direction of the head
        // signof is useful cause it returns only -1, 0 or 1
        // indicating both the direction and the distance we want here.
        // I hope that's clever.
        if (abs(diff.x) == 2 || abs(diff.y) == 2) {
          knots[i].x += signof(diff.x);
          knots[i].y += signof(diff.y);
        }
      }
      
      positions_visited_p1.insert(knots[1]);
      positions_visited_p2.insert(knots[knots.size() - 1]);
    }
  }

  return std::make_pair(positions_visited_p1.size(), positions_visited_p2.size());
}

int main () {
  auto lines = get_lines();

  Timer both_timer;
  both_timer.start();
  auto [part_one, part_two] = both(lines);
  both_timer.stop();

  std::cout << "Part one: Unique positions visited by first tail: " << part_one << std::endl;
  std::cout << "Part one: Unique positions visited by last tail: " << part_two << std::endl;
  both_timer.print_all();
}