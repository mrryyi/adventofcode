#pragma once
#include "incl.h"

namespace d03 {

    auto part1_first_try() -> std::string {
        
        auto input = util::get_lines("input\\input_03.txt");
        int64_t counter = 0;

        for(const auto& line : input) {
            // find the biggest char in the line that is NOT the last char
            // we know they will all be digits.
            // after that, find the biggest char on the right side of it.
            // the goal is to form the biggest two digit number possible.
            char biggest_char = '0';
            char biggest_char_right = '0';

            for(size_t i = 0; i < line.size() - 1; ++i) {
                char c = line[i];
                if (c > biggest_char) {
                    biggest_char = c;
                    // reset right side search
                    biggest_char_right = '0';
                    // search right side for biggest char
                    for(size_t j = i + 1; j < line.size(); ++j) {
                        char c_right = line[j];
                        if (c_right > biggest_char_right)
                            biggest_char_right = c_right;
                    }
                }
            }

            // form two digit number
            int two_digit_number = (biggest_char - '0') * 10 + (biggest_char_right - '0');
            counter += two_digit_number;
        }
        

        return std::to_string(counter);
    }

    int64_t find_biggest_number_from_x_amount_of_digits(const std::string& line, std::size_t digits) {
        std::size_t n = line.size();
        if (digits == 0 || n < digits)
            return 0;

        std::string chosen;
        chosen.reserve(digits);

        std::size_t start = 0;

        /*
        At first I approached this by iterating over the string and trying to solve it that way,
        and it just got convoluted. I tried iterative, I tried recursive, but it got very messy.

        "I'm walking over the string, sometimes picking digits, trying to improve the algorithm a bit until I arrive at the solution."

        I changed the approach to focus more on iterating over the number of digits we need to choose,
        and for each digit, find the best possible choice given the constraints.

        "I'm building a 12-digit number, one position at a time. For each position, where am I allowed to pick from?"

        One constraints being that I cannot keep looking at digits,
        if that would make it impossible to fill the remaining positions because it would leave too few digits left.
        */
        for (std::size_t pos = 0; pos < digits; ++pos) {
            std::size_t remaining = digits - pos;
            std::size_t end = n - remaining;

            char best_digit = '0';
            std::size_t best_index = start;

            for (std::size_t i = start; i <= end; ++i) {
                char c = line[i];
                if (c > best_digit) {
                    best_digit = c;
                    best_index = i;
                    if (best_digit == '9') break;
                }
            }

            chosen.push_back(best_digit);
            start = best_index + 1;
        }

        int64_t result = 0;
        for (char c : chosen)
            result = result * 10 + (c - '0');

    return result;
}

    auto part2_first_try() -> std::string {
        
        auto input = util::get_lines("input\\input_03.txt");
        int64_t counter = 0;

        for(const auto& line : input)
            counter += find_biggest_number_from_x_amount_of_digits(line, 12);
        
        return std::to_string(counter);
    }

}