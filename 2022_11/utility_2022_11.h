#pragma once
#include <fstream>
#include <vector>
#include <iostream>
#include <chrono>

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

// LOGGING
class Logger {
public:
  Logger(bool should_log) : should_log(should_log) {}

  template <typename T>
  auto& operator<<(const T& t) {
    if (should_log) {
      std::cout << t;
    }
    return *this;
  }

private:
  bool should_log;
};

// STRING STUFF
auto get_first_number_of_string(const std::string& str) -> int {
  std::string number;
  for (int i = 0; i < str.size(); ++i) {
    if (isdigit(str.at(i)) != 0) {
      while (i < str.size() && isdigit(str.at(i)) != 0) {
        number += str.at(i);
        ++i;
      }
      return std::stoi(number);
    }
  }
  return 0;
}

auto fill_longlong_vector_with_numbers_in_string(std::vector<long long>& intvector, const std::string& str) -> void {
  for (int str_i = 0; str_i < str.size(); ++str_i) {
    if (isdigit(str.at(str_i)) != 0) {
      std::string number;
      while (str_i < str.size() && isdigit(str.at(str_i)) != 0) {
        number += str.at(str_i);
        ++str_i;
      }
      intvector.push_back(std::stoi(number));
    }
  }
}

auto split_string_by_spaces(const std::string& str) -> std::vector<std::string> {
  std::stringstream ss(str);
  std::string token;
  std::vector<std::string> tokens;
  while (std::getline(ss, token, ' ')) {
    if (token != "")
      tokens.push_back(token);
  }
  return tokens;
}
