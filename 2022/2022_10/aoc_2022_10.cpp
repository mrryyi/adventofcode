#include <iostream>
#include <string>
#include <vector>

#include "utility_2022_10.h"

auto add_if_appropriate_cycle(const int cycle, const int x, int& sum) -> void {
  if (cycle % 20 == 0 && (cycle - 20) % 40 == 0) {
    // std:cout << "Signal Strength: (x * cycle): " << x << " * " << cycle << " = " << x * cycle << std::endl;
    sum += x * cycle;
  }
}

auto part_one(const std::vector<std::string>& lines) -> int {

  int x = 1;
  int sum = 0;
  int current_cycle = 0;
  for (auto line : lines) {
    ++current_cycle;
    // DURING this cycle
    add_if_appropriate_cycle(current_cycle, x, sum);

    if (line.at(0) == 'a') {
      auto pos = line.find(' ');
      auto second_part = line.substr(pos + 1);
      int to_add = std::stoi(second_part);

      // DURING this cycle
      ++current_cycle;
      add_if_appropriate_cycle(current_cycle, x, sum);
      // AFTER the above cycle
      x += to_add;
    }
  }
  
  return sum;
}

auto print_CRT_depending_on_sprite(const int cycle, const int x) -> void {
  int CRT_pos = 0;
  CRT_pos = cycle % 40 - 1;
  if (CRT_pos + 1 == x || CRT_pos == x || CRT_pos - 1 == x)
    std::cout << '#';
  else
    std::cout << '.';
  
  if (cycle % 40 == 0)
    std::cout << '\n';
}

auto part_two(const std::vector<std::string>& lines) {

  int x = 1;
  int current_cycle = 0;
  int CRT_pos = 0;
  for (auto line : lines) {
    ++current_cycle;
    // DURING this cycle
    print_CRT_depending_on_sprite(current_cycle, x);
    
    if (line.at(0) == 'a') {
      auto pos = line.find(' ');
      auto second_part = line.substr(pos + 1);
      int to_add = std::stoi(second_part);

      ++current_cycle;
      // DURING this cycle
      print_CRT_depending_on_sprite(current_cycle, x);

      // AFTER the above cycle
      x += to_add;
    }
  }
}

int main () {
  auto lines = get_lines();

  Timer part_one_timer;
  part_one_timer.start();
  int sum = part_one(lines);
  part_one_timer.stop();
  
  std::cout << "Part one: Sum: " << sum << "\n";

  Timer part_two_timer;
  part_two_timer.start();
  part_two(lines);
  part_two_timer.stop();

  std::cout << "Part one:\n"; part_one_timer.print_all(); std::cout << "\n";
  std::cout << "Part two:\n"; part_two_timer.print_all(); std::cout << std::endl;
}