#include <iostream>
#include <fstream>
#include <string>
#include <vector>

void part_one() {
  std::ifstream input_file("input.txt");

  if (!input_file.is_open()) {
    std::cout << "Error opening file" << std::endl;
  }

  int contained_ranges = 0;

  { // Loop specific block
    std::string line;
    while (std::getline(input_file, line)) {
      
      // Split line into four ints by any char that is not a digit
      std::vector<int> numbers;
      std::string number;
      for (char c : line) {
        if (isdigit(c)) {
          number += c;
        } else {
          if (!number.empty()) {
            numbers.push_back(std::stoi(number));
            number.clear();
          }
        }
      }

      // Add last number
      if (!number.empty()) {
        numbers.push_back(std::stoi(number));
        number.clear();
      }

      // First range is numbers[0] to numbers[1]
      // Second range is numbers[2] to numbers[3]
      // Extra variables for clarity, not speed.
      auto first_start = numbers[0];
      auto first_end = numbers[1];
      auto second_start = numbers[2];
      auto second_end = numbers[3];

      // check if first range is contained in second range
      if (first_start >= second_start && first_end <= second_end)
        ++contained_ranges;
      // check if second range is contained in first range
      else if (second_start >= first_start && second_end <= first_end)
        ++contained_ranges;

    }
  }

  input_file.close();

  std::cout << "Part one: Pairs where at least one range contains the other: " << contained_ranges << std::endl;
}

void part_two() {
  std::ifstream input_file("input.txt");

  if (!input_file.is_open()) {
    std::cout << "Error opening file" << std::endl;
  }

  int overlaps = 0;

  { // Loop specific block
    std::string line;
    while (std::getline(input_file, line)) {
      
      // Split line into four ints by any char that is not a digit
      std::vector<int> numbers;
      std::string number;
      for (char c : line) {
        if (isdigit(c)) {
          number += c;
        } else {
          if (!number.empty()) {
            numbers.push_back(std::stoi(number));
            number.clear();
          }
        }
      }

      // Add last number
      if (!number.empty()) {
        numbers.push_back(std::stoi(number));
        number.clear();
      }

      // First range is numbers[0] to numbers[1]
      // Second range is numbers[2] to numbers[3]
      // Extra variables for clarity, not speed.
      auto first_start = numbers[0];
      auto first_end = numbers[1];
      auto second_start = numbers[2];
      auto second_end = numbers[3];
      
      // Check if the first range overlaps the second range
      // To do that, check if the first range starts before the second range ends
      // and if the first range ends after the second range starts
      if (first_start <= second_end && first_end >= second_start)
        ++overlaps;

      // Check if the second range overlaps the first range
      else if (second_start <= first_end && second_end >= first_start)
        ++overlaps;
    }
  }

  input_file.close();

  std::cout << "Part two: Pairs where there is at least one overlap: " << overlaps << std::endl;
}

int main() {
  part_one();
  part_two();
  return 0;
}