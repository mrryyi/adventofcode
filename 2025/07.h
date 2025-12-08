#pragma once
#include "incl.h"

namespace d07 {

    auto p1() -> std::string {
        
        auto input = util::get_lines("input\\input_07.txt");
        int64_t counter = 0;
        int8_t current_beams[input.size()] = { 0 };

        for(int64_t row_idx = 0; row_idx < input.size(); ++row_idx) {
            for(int64_t char_idx = 0; char_idx < input[row_idx].size(); ++char_idx) {
                if (input[row_idx][char_idx] == '^') {
                    if (current_beams[char_idx] == 1) {
                        current_beams[char_idx] = 0;
                        current_beams[char_idx - 1] = 1;
                        current_beams[char_idx + 1] = 1;
                        counter += 1;
                    }
                }
                else if (input[row_idx][char_idx] == 'S')
                    current_beams[char_idx] = 1;
            }
        }

        return std::to_string(counter);
    }

    auto p2() -> std::string {
        
        auto input = util::get_lines("input\\input_07.txt");
        int64_t counter = 0;

        
        return std::to_string(counter);
    }
}