#include <iostream>
#include <string>
#include <vector>

#include "utility_2022_11.h"

enum OPERATION {
  noop = 1,
  old_plus_number,
  old_multiplied_by_number,
  old_multiplied_by_old
};

struct Monkey {
  int id;
  std::vector<long long> items;
  
  OPERATION operation_type = noop;
  int operation_number = 0;

  int test_divisible_by;
  int throw_monkey_if_true;
  int throw_monkey_if_false;

  int inspections = 0;

  void print_all() {
    std::cout << "Monkey " << id << ":\n";
    std::cout << "  Starting_items: ";
    for(auto item : items) { std::cout << item << " "; } std::cout << "\n";
    std::cout << "  operation_type: ";
    switch (operation_type) {
      case noop: std::cout << "noop"; break;
      case old_plus_number: std::cout << "old + " << operation_number; break;
      case old_multiplied_by_number: std::cout << "old * " << operation_number; break;
      case old_multiplied_by_old: std::cout << "old * old"; break;
    }
    std::cout << "\n";
    
    std::cout << "  Test: Divisible by " << test_divisible_by << "\n";
    std::cout << "    If true: throw to monkey "  << throw_monkey_if_true  << "\n";
    std::cout << "    If false: throw to monkey " << throw_monkey_if_false << "\n";
  }
};


auto get_monkeys(const std::vector<std::string>& lines) -> std::vector<Monkey> {
  std::vector<Monkey> monkeys;
  
  for (int line_i = 0; line_i < lines.size(); ++line_i) {
    if (lines.at(line_i).find("Monkey") != std::string::npos) {
      Monkey monkey;
      monkey.id = get_first_number_of_string(lines.at(line_i));
      ++line_i;

      fill_longlong_vector_with_numbers_in_string(monkey.items, lines.at(line_i));      
      ++line_i;

      auto operation_tokens = split_string_by_spaces(lines.at(line_i));
      if (operation_tokens.at(4) == "+") {
        monkey.operation_type = old_plus_number;
        monkey.operation_number = std::stoi(operation_tokens.at(5));
      } else if (operation_tokens.at(4) == "*" && operation_tokens.at(5) != "old") {
        monkey.operation_type = old_multiplied_by_number;
        monkey.operation_number = std::stoi(operation_tokens.at(5));
      } else if (operation_tokens.at(4) == "*") {
        monkey.operation_type = old_multiplied_by_old;
      }
      ++line_i;
      
      monkey.test_divisible_by = get_first_number_of_string(lines.at(line_i));
      ++line_i;

      monkey.throw_monkey_if_true = get_first_number_of_string(lines.at(line_i));
      ++line_i;
      
      monkey.throw_monkey_if_false = get_first_number_of_string(lines.at(line_i));
      monkeys.push_back(monkey);
    }
  }
  return monkeys;
}  

// replacement to cout that only prints if should_log is true


auto both_parts(const std::vector<std::string>& lines, const int rounds = 20, const int divide_factor = 3) -> long long {
  
  auto monkeys = get_monkeys(lines);

  long long lowest_common_modulo = 1;
  for (const auto& monkey : monkeys)
    lowest_common_modulo *= monkey.test_divisible_by;
  
  for (int round = 1; round <= rounds; ++round) {
    for (auto& monkey : monkeys) {
      for (auto& worry_level : monkey.items) {
        monkey.inspections += 1;

        switch(monkey.operation_type) {
          case old_plus_number:           worry_level += monkey.operation_number; break;
          case old_multiplied_by_number:  worry_level *= monkey.operation_number; break;
          case old_multiplied_by_old:     worry_level *= worry_level; break;
        }

        // if you don't do this, you will search for bigint libraries
        // and wait for the program to finish in exponential time
        worry_level %= lowest_common_modulo;

        if (divide_factor != 1 && divide_factor != 0)
          worry_level = worry_level / divide_factor;

        if (worry_level % monkey.test_divisible_by == 0)
          monkeys.at(monkey.throw_monkey_if_true).items.push_back(worry_level);
        else
          monkeys.at(monkey.throw_monkey_if_false).items.push_back(worry_level);
      }

      // Monkey threw away all items to another monkey.
      monkey.items.clear();
    }
  }

  int  second_max_inspections = 0;
  int  max_inspections = 0;
  for (auto& monkey : monkeys) {
    if (monkey.inspections > max_inspections) {
      second_max_inspections = max_inspections;
      max_inspections = monkey.inspections;
    }
  }

  return max_inspections * second_max_inspections;
}


int main () {
  auto lines = get_lines();

  Timer part_one_timer;
  part_one_timer.start();
  long long shenanigans_p1 = both_parts(lines);
  part_one_timer.stop();
  
  std::cout << "Part one: shenanigans: " << shenanigans_p1 << "\n";
  part_one_timer.print_all(); std::cout << "\n";
  
  Timer part_two_timer;
  part_two_timer.start();
  long long shenanigans_p2 = both_parts(lines, 10000, 1);
  part_two_timer.stop();

  std::cout << "Part two: shenanigans: " << shenanigans_p2 << "\n";
  part_two_timer.print_all(); std::cout << "\n";

}