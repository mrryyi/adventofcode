#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <map>

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

using crate = char;

auto parse_stack_descriptors(const std::vector<std::string>& lines) -> std::map<int, std::stack<crate>> {

  // Length of e.g. "[F] " note the space after the closing bracket.
  const int STACK_DESCRIPTOR_LENGTH = 4;
  int length_of_stack_descriptor_line = lines[0].size();
  int stack_amount = length_of_stack_descriptor_line / STACK_DESCRIPTOR_LENGTH;
  
  int first_empty_line = 0;
  for (int i = 0; i < lines.size(); ++i) {
    if (lines[i].empty()) {
      first_empty_line = i;
      break;
    }
  }

  int first_filedescriptor_line = first_empty_line - 2;

  // Initialize stacks. Start at 1 because that's what the input says.
  std::map<int, std::stack<crate>> stacks;
  for(int stack_i = 1; stack_i <= stack_amount; ++stack_i)
    stacks[stack_i] = std::stack<crate>();

  // Parse stack descriptor lines from the first empty line reversed to top of file
  // Why reversed? To push the lowest characters first into the stacks.
  for (int line_i = first_filedescriptor_line; line_i >= 0; --line_i) {
    // If we find a [ anywhere in the line then we are on a stack descriptor line
    if (lines[line_i].find('[') != std::string::npos) {
      int stack_i = 1;
      // Let crate_i start at 1 because we know 0th char is '['
      for (int crate_i = 1; crate_i < lines[line_i].size(); crate_i += STACK_DESCRIPTOR_LENGTH) {
        crate c = lines[line_i][crate_i];

        // cause it could be a space.
        if (c >= 'A' && c <= 'Z')
          stacks[stack_i].push(c);
        stack_i += 1;
      }
    }
  }

  return stacks;
}

struct move {
  int amount;
  int from_stack;
  int to_stack;
};

auto parse_moves(const std::vector<std::string>& lines) -> std::vector<move> {
  std::vector<move> moves;
  for (auto const& line : lines) {
    if (line.find("move") != std::string::npos) {
      move m;
      sscanf(line.c_str(), "move %d from %d to %d", &m.amount, &m.from_stack, &m.to_stack);
      moves.push_back(m);
    }
  }
  return moves;
}

auto part_one(const std::vector<std::string>& lines) -> void {
  
  auto stacks = parse_stack_descriptors(lines);
  auto moves = parse_moves(lines);
  
  for (auto const& move : moves) {
    for (int i = 0; i < move.amount; ++i) {
      crate c = stacks[move.from_stack].top();
      stacks[move.from_stack].pop();
      stacks[move.to_stack].push(c);
    }
  }

  for (auto const& [stack_i, stack] : stacks)
    std::cout << stack.top();
  std::cout << std::endl;
}

auto part_two(const std::vector<std::string>& lines) -> void {

  auto stacks = parse_stack_descriptors(lines);
  auto moves = parse_moves(lines);
  
  for (auto const& move : moves) {
    // Only one, no need for any vector theatrics.
    if (move.amount == 1) {
      crate c = stacks[move.from_stack].top();
      stacks[move.from_stack].pop();
      stacks[move.to_stack].push(c);
    }
    else {
      // Crane picks up crates from the stack in the order they are on the stack.
      std::vector<crate> crane;
      for (int i = 0; i < move.amount; ++i) {
        crate c = stacks[move.from_stack].top();
        stacks[move.from_stack].pop();
        crane.push_back(c);
      }

      // Crane lowers down the crates in the preserved order they were picked up.
      for (int i = crane.size() - 1; i >= 0; --i)
        stacks[move.to_stack].push(crane[i]);
    }
  }
  
  for (auto const& [stack_i, stack] : stacks)
    std::cout << stack.top();
  std::cout << std::endl;
}

int main() {
  auto lines = get_lines();
  part_one(lines);
  part_two(lines);
  return 0;
}