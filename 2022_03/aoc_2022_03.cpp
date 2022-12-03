#include <iostream>
#include <fstream>
#include <string>
#include <vector>

int priority_of_item(char c) {
    // 'a' through 'z' are 97 through 122, so subtract 96 to get 1 through 26
    // 'A' through 'Z' are 65 through 90, so subtract 38 to get 27 through 52
    if (c >= 'a')
      return c - 96;
    else
      return c - 38;
}

void part_one() {
  std::ifstream input_file("input.txt");

  if (!input_file.is_open()) {
    std::cout << "Error opening file" << std::endl;
  }

  int sum_of_priorities = 0;

  { // Loop specific block
    std::string line;
    while (std::getline(input_file, line)) {
      
      // Split line into two strings
      const std::string first_compartment = line.substr(0, line.size() / 2);
      const std::string second_compartment = line.substr(line.size() / 2, line.size());

      // Find first letter that are in both compartments
      char common_item = ' ';
      
      for (auto const& c : first_compartment) {
        if (second_compartment.find(c) != std::string::npos) {
          common_item = c;
          break;
        }
      }
      
      if (common_item != ' ')
        sum_of_priorities += priority_of_item(common_item);
      
    }
  }

  input_file.close();

  std::cout << "Part one: Sum of priorities: " << sum_of_priorities << std::endl;
}

void part_two() {
  std::ifstream input_file("input.txt");

  if (!input_file.is_open()) {
    std::cout << "Error opening file" << std::endl;
  }

  int sum_of_priorities = 0;

  { // Loop specific block
    std::string line;
    std::vector<std::string> lines_of_threegroup;
    while (std::getline(input_file, line)) {
      
      lines_of_threegroup.push_back(line);
      
      if (lines_of_threegroup.size() == 3) {
        // Find first letter that are in all three compartments
        char common_item = ' ';
        
        for (auto const& c : lines_of_threegroup[0]) {
          if (lines_of_threegroup[1].find(c) != std::string::npos && lines_of_threegroup[2].find(c) != std::string::npos) {
            common_item = c;
            break;
          }
        }
        
        if (common_item != ' ')
          sum_of_priorities += priority_of_item(common_item);
        
        // Make space for next three lines
        lines_of_threegroup.clear();
      }
    }
  }

  input_file.close();

  std::cout << "Part two: Sum of priorities: " << sum_of_priorities << std::endl;
}

int main() {
  part_one();
  part_two();
  return 0;
}