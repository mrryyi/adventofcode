#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

// Could just be ints but this is clear and adaptable in case.
struct elf {
  int carried_calories;
};

int main()
{
  // Open file
  std::ifstream input_file("input.txt");

  if (!input_file.is_open()) {
    std::cout << "Error opening file" << std::endl;
    return 1;
  }

  // Data storage
  std::vector<elf> elfcarries;

  { // Loop specific block
    bool new_elfcarry = true;
    std::string line;

    while (std::getline(input_file, line)) {
      if (line.size() > 0) {
        if (new_elfcarry)
          elfcarries.push_back(elf());

        elfcarries.back().carried_calories += std::stoi(line);

        new_elfcarry = false;
      }
      else
        new_elfcarry = true;
    }
  }

  input_file.close();

  { // Sorting block
    auto sort_lambda = [](const elf& a, const elf& b) {
      return a.carried_calories < b.carried_calories;
    };

    std::sort(elfcarries.begin(), elfcarries.end(),
              sort_lambda);
  }

  int third_most_calories = 0;
  int second_most_calories = 0;
  int most_calories = 0;

  if (elfcarries.size() >= 3) {
    third_most_calories = elfcarries[elfcarries.size() - 3].carried_calories;
    second_most_calories = elfcarries[elfcarries.size() - 2].carried_calories;
  }

  if (elfcarries.size() >= 1)
    most_calories = elfcarries[elfcarries.size() - 1].carried_calories;

  std::cout << "Part one: Most calories carried by elf: " << most_calories;
  std::cout << "\nPart two: Calories of top three elves: " << most_calories + second_most_calories + third_most_calories << std::endl;

  return 0;
}