#pragma once
#include "incl.h"

namespace d08 {

    struct Box {
        int64_t x = 0;
        int64_t y = 0;
        int64_t z = 0;
    };

    
    auto parse_number(const char*& p) {
        int64_t value;
        auto end = p + strlen(p);
        std::from_chars(p, end, value);
        while (*p != ',' && *p != '\0') ++p;
        if (*p == ',') ++p;
        return value;
    }

    auto p1() -> std::string {
        
        auto input = util::get_lines("input\\input_08.txt");
        uint64_t counter = 0;
        std::vector<Box> boxes;
        boxes.reserve(input.size());

        for (auto &line : input) {
            const char *p = line.c_str();
            Box b;
            b.x = parse_number(p);
            b.y = parse_number(p);
            b.z = parse_number(p);
            boxes.push_back(b);
        }

        return std::to_string(counter);
    }


    auto p2() -> std::string {
        
        auto input = util::get_lines("input\\input_08.txt");
        uint64_t counter = 1;
        
        return std::to_string(counter);
    }
}