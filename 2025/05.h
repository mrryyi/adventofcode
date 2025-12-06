#pragma once
#include "incl.h"

namespace d05 {

    // idk why tf i didn't just use structs from the start
    // but whatever
    // a vector of pairs is less clear than a vector of structs
    // i dont even know if it is more performative
    // probably not, since i need to push back two items at a time
    // and access two items at a time
    // so structs make more sense
    // but whatever
    // i wanted to do it this way.
    auto part1_first_try() -> std::string {
        
        auto input = util::get_lines("input\\input_05.txt");
        int64_t counter = 0;

        std::vector<int64_t> ranges;
        std::vector<int64_t> numbers;

        bool looking_for_space = true;

        int64_t index = 0;
        while (looking_for_space || index < input.size()) {
            if (input[index].size() < 2) {
                looking_for_space = false;
                break;
            }

            const std::string& line = input[index];
            size_t dash_pos = line.find('-');

            int64_t start = 0;
            std::from_chars(line.data(), line.data() + dash_pos, start);
            int64_t end = 0;
            std::from_chars(line.data() + dash_pos + 1, line.data() + line.size(), end);

            ranges.push_back(start);
            ranges.push_back(end);

            ++index;
        }
        ++index; // skip the empty line

        while (index < input.size()) {
            if (input[index].empty())
                break;
            int64_t number = 0;
            std::from_chars(input[index].data(), input[index].data() + input[index].size(), number);
            numbers.push_back(number);

            ++index;
        }

        for(std::size_t number_idx = 0; number_idx < numbers.size(); ++number_idx) {
            int64_t number = numbers[number_idx];

            for(std::size_t range_idx = 0; range_idx < ranges.size(); range_idx += 2) {
                int64_t start = ranges[range_idx];
                int64_t end = ranges[range_idx + 1];

                if (number >= start && number <= end) {
                    ++counter;
                    break;
                }
            }
        }
        
        
        return std::to_string(counter);
    }

    struct range {
        int64_t start;
        int64_t end;

        // for debugging
        friend std::ostream& operator<<(std::ostream& os, const range& r) {
            os << "[" << r.start << "-" << r.end << "]";
            return os;
        }
    };

    auto part2_first_try() -> std::string {
        
        auto input = util::get_lines("input\\input_05.txt");
        int64_t counter = 0;

        std::vector<range> ranges;

        bool looking_for_space = true;

        int64_t index = 0;
        while (looking_for_space || index < input.size()) {
            if (input[index].size() < 2) {
                looking_for_space = false;
                break;
            }

            const std::string& line = input[index];
            size_t dash_pos = line.find('-');

            int64_t start = 0;
            std::from_chars(line.data(), line.data() + dash_pos, start);
            int64_t end = 0;
            std::from_chars(line.data() + dash_pos + 1, line.data() + line.size(), end);

            ranges.push_back(range{start, end});

            ++index;
        }

        // Now we need to coalesce ranges that overlap.

        // It's easy to do with a sort first.
        std::sort(ranges.begin(), ranges.end(), [](const range& a, const range& b) {
            return a.start < b.start;
        });
        
        // we need to make sure that all ranges have been checked against each other,
        // so we use a loop that restarts when a change has been made.
        // i dont know if there's a more efficient way to do this
        // but coming up with a solution that doesn't redo changes will take an order of magnitude more brainpower than this simple approach
        // KISS principle and all that.
        // code is more maintainable if it's readable.
        // then again, this is just for advent of code, so who cares.
        // i mean, you may want to use AoC to practice writing maintainable code or you may want to practice writing performant code,
        // but at the same time, it's just a fun exercise, so whatever.
        // what I like to do is solve it, and then optimize it, but if I don't want to after solving it, then I don't.
        // Sometimes I want to optimize it, but I am not smart/diligent enough, so I leave it as is even though it frustrates me.
        bool changed = true;
        while (changed) {
            changed = false;
            for(std::size_t i = 0; i < ranges.size() - 1; ++i) {
                range& current = ranges[i];
                range& next = ranges[i + 1];

                if (current.end >= next.start) {
                    // merge those fuckers
                    current.end = std::max(current.end, next.end);
                    ranges.erase(ranges.begin() + i + 1);
                    changed = true;
                    break;
                }
            }
        }
        
        /*
            std::cout << "Coalesced ranges: " << std::endl;
            for(const auto& r : ranges)
                std::cout << r << std::endl;
        */
        
        for(const auto& r : ranges)
            counter += (r.end - r.start + 1);
        
        return std::to_string(counter);
    }
}