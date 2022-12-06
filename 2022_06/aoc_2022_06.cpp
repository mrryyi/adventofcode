#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <queue>

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

auto all_deque_chars_different(const std::deque<char>& queue) -> bool {
  for (auto c : queue) {
    if (std::count(queue.begin(), queue.end(), c) > 1)
      return false;
  }
  return true;
}

auto part_one(const std::vector<std::string>& lines) -> void {
  for (auto line : lines) {
    std::deque<char> queue;
    int char_index = 0;  
    for (auto c : line) {
      queue.push_back(c);

      if (queue.size() > 4)
        queue.pop_front();
      
      if (queue.size() == 4 && all_deque_chars_different(queue)) 
          break;

      ++char_index;
    }

    std::cout << "Part one: chars processed: " << char_index + 1 << std::endl;
  }
}

auto part_two(const std::vector<std::string>& lines) -> void {
  for (auto line : lines) {
    std::deque<char> queue;
    int char_index = 0;  
    for (auto c : line) {
      queue.push_back(c);

      if (queue.size() > 14)
        queue.pop_front();
      
      if (queue.size() == 14 && all_deque_chars_different(queue)) 
          break;

      ++char_index;
    }

    std::cout << "Part two: chars processed: " << char_index + 1 << std::endl;
  }
}

int main() {
  auto lines = get_lines();
  part_one(lines);
  part_two(lines);
  return 0;
}