#pragma once
#include "incl.h"

namespace d06 {

    constexpr char8_t multiply = '*';
    constexpr char8_t add= '+'; 

    // Goddamn this is so ugly and contains so much unnecessary stuff.
    // Fixing this in p1_op1
    auto p1() -> std::string {
        
        auto input = util::get_lines("input\\input_06.txt");
        int64_t counter = 0;

        std::string::iterator iterators[4];
        for(std::size_t line_idx = 0; line_idx < input.size() - 1; ++line_idx)
            iterators[line_idx] = input[line_idx].begin();
        
        std::vector<char8_t> operations;
        for(std::size_t row_idx = 0; row_idx < input[4].size(); ++row_idx)
            if (input[4][row_idx] == multiply || input[4][row_idx] == add)
                operations.push_back(input[4][row_idx]);
        auto operation_iterator = operations.begin();

        int64_t nums[4] = { 0, 0, 0, 0 };
        while (operation_iterator != operations.end()) {
            // Extract the numbers per row.
            for(std::size_t line_idx = 0; line_idx < input.size() - 1; ++line_idx) {
                
                bool number_found = false;
                nums[line_idx] = 0;
                while((*iterators[line_idx] != ' ' || nums[line_idx] == 0) && iterators[line_idx] != input[line_idx].end()) {
                    char c = *iterators[line_idx];
                    if (c != ' ')
                        nums[line_idx] = nums[line_idx] * 10 + (c - '0');
                    ++iterators[line_idx];
                }
            }

            // Perform the operation.
            int64_t multiply_result = 1;
            switch (*operation_iterator) {
                case multiply:
                    multiply_result = 1;
                    for(auto const& num : nums)
                        multiply_result = multiply_result * num;
                    counter += multiply_result;
                    break;
                case add:
                    for(auto const& num : nums)
                        counter += num;
                    break;
                default:
                    throw;
                    break;
            }
            ++operation_iterator;
        }
        
        
        return std::to_string(counter);
    }

    // The numbers in the data are all 4 digits long
    // and therefore, despite rotating reading direction by 90 degrees
    // we still just have 4 numbers
    auto p2() -> std::string {
        
        auto input = util::get_lines("input\\input_06.txt");
        int64_t counter = 0;

        int64_t nums[4] = { 0, 0, 0, 0 };
        int64_t column_index = 0;
        int64_t num_index = 0;
        char8_t operation = -1;
        int64_t multiply_result = 1;

        while (column_index < input[0].size()) {
            if (input[4][column_index] != ' ') {
                // New set of numbers to operate on as we have a new operation.
                nums[0] = 0;
                nums[1] = 0;
                nums[2] = 0;
                nums[3] = 0;
                num_index = 0;
                operation = input[4][column_index];
            }
            
            bool empty_column = true;
            for(std::size_t line_idx = 0; line_idx < input.size() - 1; ++line_idx) {
                char c = input[line_idx][column_index];
                if (c != ' ') {
                    nums[num_index] = nums[num_index] * 10 + (c - '0');
                    empty_column = false;
                }
            }

            if ((operation != -1) // Not the first 
                && (
                        empty_column                        // empty column - calculate the numbers that we got.
                    ||  column_index + 1 >= input[0].size() // End of file - calculate the numbers that we got.
                    )
                ) {
                switch (operation) {
                    case multiply:
                        multiply_result = 1;
                        for(auto const& num : nums)
                            multiply_result = multiply_result * (num != 0 ? num : 1);
                        counter += multiply_result;
                        break;
                    case add:
                        for(auto const& num : nums)
                            counter += num;
                        break;
                    default:
                        throw;
                        break;
                }
            }
            ++column_index;
            ++num_index;
        }
        
        
        return std::to_string(counter);
    }
}