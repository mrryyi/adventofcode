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
