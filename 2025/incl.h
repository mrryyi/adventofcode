#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <chrono>
#include <charconv>
#include <cstring>
#include <climits>
#include <unordered_set>
#include <unordered_map>

namespace util {

    auto get_lines(const std::string& path) -> std::vector<std::string> {
        std::ifstream input_file(path);

        if (!input_file.is_open()) {
            std::cout << "Error opening file" << std::endl;
            throw;
        }

        std::vector<std::string> lines;
        std::string line;
        while (std::getline(input_file, line))
            lines.push_back(line);

        return lines;
    }

    auto get_single_line(const std::string& path) -> std::string {
        std::ifstream input_file(path);

        if (!input_file.is_open()) {
            std::cout << "Error opening file" << std::endl;
            throw;
        }

        std::string line;
        std::getline(input_file, line);
        return line;
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

    int numDigits64bit(int64_t x) {
        if (x >= 10000000000) {
            if (x >= 100000000000000) {
                if (x >= 10000000000000000) {
                    if (x >= 100000000000000000) {
                        if (x >= 1000000000000000000)
                            return 19;
                        return 18;
                    }
                    return 17;
                }
                if (x >= 1000000000000000)
                    return 16;
                return 15;
            } 
            if (x >= 1000000000000) {
                if (x >= 10000000000000)
                    return 14;
                return 13;
            }
            if (x >= 100000000000)
                return 12;
            return 11;
        }
        if (x >= 100000) {
            if (x >= 10000000) {
                if (x >= 100000000) {
                    if (x >= 1000000000)
                        return 10;
                    return 9;
                }
                return 8;
            }
            if (x >= 1000000)
                return 7;
            return 6;
        }
        if (x >= 100) {
            if (x >= 1000) {
                if (x >= 10000)
                    return 5;
                return 4;
            }
            return 3;
        }
        if (x >= 10)
            return 2;
        return 1;
    }
}