#pragma once
#include "incl.h"

namespace d04 {

    auto part1_first_try() -> std::string {
        
        auto input = util::get_lines("input\\input_04.txt");
        int64_t counter = 0;
        std::size_t roll_length = input[0].size();
        for(std::size_t line_idx = 0; line_idx < input.size(); ++line_idx) {
            const bool at_top = (line_idx == 0);
            const bool at_bottom = (line_idx == input.size() - 1);
            for(std::size_t roll_idx = 0; roll_idx < roll_length; ++roll_idx) {
                char current_char = input[line_idx][roll_idx];
                
                if (current_char != '@')
                    continue;
                
                int neighbouring_rolls = 0;
                
                const bool at_left = (roll_idx == 0);
                const bool at_right = (roll_idx == roll_length - 1);
                
                // check the 8 neighbours - if any are == '@', increase neighbouring_rolls

                // top
                if (!at_top) {
                    if (!at_left && input[line_idx - 1][roll_idx - 1] == '@')
                        ++neighbouring_rolls;
                    if (input[line_idx - 1][roll_idx] == '@')
                        ++neighbouring_rolls;
                    if (!at_right && input[line_idx - 1][roll_idx + 1] == '@')
                        ++neighbouring_rolls;
                }

                // middle
                if (!at_left && input[line_idx][roll_idx - 1] == '@')
                    ++neighbouring_rolls;
                if (!at_right && input[line_idx][roll_idx + 1] == '@')
                    ++neighbouring_rolls;

                // bottom
                if (!at_bottom) {
                    if (!at_left && input[line_idx + 1][roll_idx - 1] == '@')
                        ++neighbouring_rolls;
                    if (input[line_idx + 1][roll_idx] == '@')
                        ++neighbouring_rolls;
                    if (!at_right && input[line_idx + 1][roll_idx + 1] == '@')
                        ++neighbouring_rolls;
                }

                if (neighbouring_rolls < 4)
                    ++counter;
            }
        }

        return std::to_string(counter);
    }


    auto part2_first_try() -> std::string {
        
        auto input = util::get_lines("input\\input_04.txt");
        int64_t counter = 0;
        std::size_t roll_length = input[0].size();

        int64_t removed_rolls_this_iteration = 0;

        while (removed_rolls_this_iteration > 0 || counter == 0) {
            removed_rolls_this_iteration = 0;
            for(std::size_t line_idx = 0; line_idx < input.size(); ++line_idx) {
                const bool at_top = (line_idx == 0);
                const bool at_bottom = (line_idx == input.size() - 1);
                for(std::size_t roll_idx = 0; roll_idx < roll_length; ++roll_idx) {
                    char current_char = input[line_idx][roll_idx];
                    
                    if (current_char != '@')
                        continue;
                    
                    int neighbouring_rolls = 0;
                    
                    const bool at_left = (roll_idx == 0);
                    const bool at_right = (roll_idx == roll_length - 1);
                    
                    // check the 8 neighbours - if any are == '@', increase neighbouring_rolls

                    // top
                    if (!at_top) {
                        if (!at_left && input[line_idx - 1][roll_idx - 1] == '@')
                            ++neighbouring_rolls;
                        if (input[line_idx - 1][roll_idx] == '@')
                            ++neighbouring_rolls;
                        if (!at_right && input[line_idx - 1][roll_idx + 1] == '@')
                            ++neighbouring_rolls;
                    }

                    // middle
                    if (!at_left && input[line_idx][roll_idx - 1] == '@')
                        ++neighbouring_rolls;
                    if (!at_right && input[line_idx][roll_idx + 1] == '@')
                        ++neighbouring_rolls;

                    // bottom
                    if (!at_bottom) {
                        if (!at_left && input[line_idx + 1][roll_idx - 1] == '@')
                            ++neighbouring_rolls;
                        if (input[line_idx + 1][roll_idx] == '@')
                            ++neighbouring_rolls;
                        if (!at_right && input[line_idx + 1][roll_idx + 1] == '@')
                            ++neighbouring_rolls;
                    }

                    if (neighbouring_rolls < 4) {
                        ++removed_rolls_this_iteration;
                        input[line_idx][roll_idx] = '.'; // mark as removed
                    }
                }
            }
            counter += removed_rolls_this_iteration;
        }

        return std::to_string(counter);
    }
}