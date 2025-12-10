#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

auto get_line() -> std::string {
  std::ifstream input_file("input.txt");

  if (!input_file.is_open())
    std::cout << "Error opening file" << std::endl;

  std::string line;
  std::getline(input_file, line);

  return line;
}

auto all_deque_chars_different(const std::deque<char>& queue) -> bool {
  for (auto c : queue) 
    if (std::count(queue.begin(), queue.end(), c) > 1)
      return false;
  return true;
}

auto count_of_chars_before_n_unique_chars(const std::string& line, int n) -> int {
  std::deque<char> queue;
  int chars_processed = 0;

  for (auto c : line) {
    ++chars_processed;
    queue.push_back(c);

    if (queue.size() > n)
      queue.pop_front();
    
    if (queue.size() == n && all_deque_chars_different(queue)) 
        break;
  }

  return chars_processed;
}

auto part_one(const std::string line) -> void {
  std::cout << "Part one: chars processed: ";
  std::cout << count_of_chars_before_n_unique_chars(line, 4) << std::endl;
}

auto part_two(const std::string line) -> void {
  std::cout << "Part two: chars processed: ";
  std::cout << count_of_chars_before_n_unique_chars(line, 14) << std::endl;
}

int main() {
  auto line = get_line();
  part_one(line);
  part_two(line);
  return 0;
}