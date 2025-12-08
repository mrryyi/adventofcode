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

    // My first attempt worked for the small example, but of course not for the real puzzle input.
    // It was the same function, but instead of returning total, it simply increased a counter for every split,
    // naively counting each time we branch.
    //
    // Having thought about timelines before, one can only imagine the amount of branching paths.
    // I wanted to see for myself just how immense the increase was for the puzzle input, just to see if it was possible
    // to brute force it.
    // While knowing that it would be massive, I find it difficult to visualize what the effect would be in real time.
    //
    // 12 472 142 047 197 timelines was the count for my puzzle input.
    // That would be a lot of CPU cycles.
    // 
    // AoC has so many benefits. You can make it into whatever you want.
    // But one that I find very valuable is the upgrade to the thinking of
    // those who have perhaps not had to think about performance before.
    // New developers, front-end developers, or simply a hobby coder.
    // When faced with being able to solve it computationally, but then
    // having to get creative about how to solve it effectively (or looking up how to do it.) 
    //
    // It is always great to arrive at a naive solution first, to logically be able to solve the puzzle.
    // That puts the computational part complete.
    // Making it run with a not shit time complexity can only (dont quote me) be done after it actually
    // does as advertised, even if slow.

    // There is one thing I would like to learn though for the 'optimization'.
    // While the recursive solution is elegant,
    // I'd love to learn more about how to turn problems that are naturally recursive into iterative code.
    auto timeline_split(std::unordered_map<uint64_t, int64_t>& memo,
                        const std::vector<std::string>& input,
                        uint64_t& split_count,
                        uint32_t row_idx,
                        const int32_t beam_col) -> uint64_t {
        
        const int64_t rows = input.size();
        // increase row_idx until finding splitter for the beam.
        // When finding splitter for the beam, call the function twice, one for each new position created.
        // When those functions return, add up the total and return
        // but not before creating a key for how many timeline splits will occur for that splitter
        // so we can do a lookup+skip if we see that splitter again.

        uint64_t key = uint64_t(row_idx) << 32 | uint64_t(beam_col);
        if (memo.contains(key))
            return memo[key];

        for(++row_idx; row_idx < rows; ++row_idx) {
            if (input[row_idx][beam_col] == '^') {
                uint64_t total = 1; // Cause this split counts too.
                
                total += timeline_split(memo, input, split_count, row_idx, beam_col - 1);
                total += timeline_split(memo, input, split_count, row_idx, beam_col + 1);
                
                memo[key] = total;
                return total;
            }
        }

        memo[key] = 0;
        return 0;
    }

    auto p2() -> std::string {
        
        auto input = util::get_lines("input\\input_07.txt");
        std::unordered_map<uint64_t, int64_t> memo;
        uint64_t split_count = 1;
        split_count += timeline_split(memo, input, split_count, 0, input[0].size() / 2);
        
        return std::to_string(split_count);
    }
}