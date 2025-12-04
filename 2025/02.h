#pragma once
#include "incl.h"

namespace d02 {

    auto test() -> void {
        int64_t start = 100000;
        int64_t end = 200000;
        for(int i = start; i <= end; ++i) {
            int digits = util::numDigits64bit(i);
            if (digits % 2 == 0) {
                // Check for sameness
                int half_digits = digits/2;
                int div = 1;
                for(int j = 0; j < half_digits; ++j)
                    div *= 10;

                int left_half = (i / div);
                int right_half = i - (left_half * div);
                
                if (left_half == right_half)
                    std::cout << "number: " << i <<  " left = " << left_half << " right = " << right_half << std::endl; 
            }
        }

    }

    auto part1_first_try() -> std::string {
        
        auto input = util::get_single_line("input\\input_02.txt");
        char * token;
	    char * cStrToSplit = strdup(input.c_str());
	    token = strtok (cStrToSplit,",");
        int64_t counter = 0;
        while (token != NULL)
        {
            std::string str(token);
            int64_t start = 0;
            int64_t end = 0;

            std::string::iterator it = str.begin();

            while (*it != '-') {
                char c = *it;
                start = start * 10 + (c - '0');
                ++it;
            }
            ++it;
            while (it != str.end()) {
                char c = *it;
                end = end * 10 + (c - '0');
                ++it;
            }
            std::cout << start << "-" << end << std::endl;

            for(int64_t i = start; i <= end; ++i) {
                if (i < 0)
                    std::cout << "what the fuck. i = " << i << "." << std::endl;
                int digits = util::numDigits64bit(i);
                if (digits % 2 == 0) {
                    // Check for sameness
                    int half_digits = digits/2;
                    int64_t div = 1;
                    for(int j = 0; j < half_digits; ++j)
                        div *= 10;

                    int64_t left_half = (i / div);
                    int64_t right_half = i - (left_half * div);
                    
                    if (left_half == right_half) {
                        if (counter + i < 0)
                            std::cout << "overflow at " << i << "." << std::endl;
                        counter += i;
                    }

                }
                else {
                    std::cout << i << ": Detecting non-divisible-by-2 digit amount, ";
                    int64_t nextOrderOfMagnitude = 1;
                    for(int j = 0; j < digits; ++j)
                        nextOrderOfMagnitude *= 10;
                    
                    if (nextOrderOfMagnitude > end) {
                        std::cout << "and there will be no more in this range. Skipping." << std::endl;
                        break;
                    }
                    else {
                        std::cout << "but there will come more - fastforwarding to next order of magnitude: " << nextOrderOfMagnitude << std::endl;
                        i = nextOrderOfMagnitude;
                    }
                }
            }
            
            token = strtok (NULL, ",");
        }

        return std::to_string(counter);
    }

    auto part1_op_01() -> std::string {
        
        auto input = util::get_single_line("input\\input_02.txt");
        char * token;
	    char * cStrToSplit = strdup(input.c_str());
	    token = strtok (cStrToSplit,",");
        int64_t counter = 0;
        while (token != NULL)
        {
            int64_t start = 0;
            int64_t end = 0;
            
            std::string str(token);
            std::string::iterator it = str.begin();

            while (*it != '-') {
                char c = *it;
                start = start * 10 + (c - '0');
                ++it;
            }
            ++it; // ',' comma
            while (it != str.end()) {
                char c = *it;
                end = end * 10 + (c - '0');
                ++it;
            }

            for(int64_t i = start; i <= end; ++i) {
                int digits = util::numDigits64bit(i);
                if (digits % 2 == 0) {
                    // Check for sameness
                    int half_digits = digits/2;
                    int64_t div = 1;
                    for(int j = 0; j < half_digits; ++j)
                        div *= 10;

                    int64_t left_half = (i / div);
                    int64_t right_half = i - (left_half * div);
                    
                    if (left_half == right_half)
                        counter += i;

                }
                else {
                    int64_t nextOrderOfMagnitude = 1;
                    for(int j = 0; j < digits; ++j)
                        nextOrderOfMagnitude *= 10;
                    
                    if (nextOrderOfMagnitude > end)
                        break;
                    else 
                        i = nextOrderOfMagnitude;
                }
            }
            
            token = strtok (NULL, ",");
        }

        return std::to_string(counter);
    }

    auto testmodulo() -> void {
        int64_t b = 123123123123;
        int64_t modulo = 1;
        for(int i = 1; i <= 12; ++i){
            modulo = modulo * 10;
            std::cout << b << "% " << modulo << " = " << b % modulo << std::endl;

        }
    }

    // I can't be arsed to optimize this.
    // I just KNOW it can complete the task so much faster, 
    // I KNOW it checks numbers that unnecessary.
    // I KNOW there are ways to make it better.
    // Thoughts:
    // If we know the magnitude of all numbers in a range, up until the next order of magnitude,
    // can we use that to our advantage and not have to calculate some of this stuff each call?
    auto patternFinder(int64_t i, int64_t digits) -> bool
    {    
        constexpr int64_t magnitude[18] =
        {
            1,
            10,
            100,
            1000,
            10000,
            100000,
            1000000,
            10000000,
            100000000,
            1000000000,
            10000000000,
            100000000000,
            1000000000000,
            10000000000000,
            100000000000000,
            1000000000000000,
            10000000000000000,
            100000000000000000
        //  9223372036854775807 max int64
        };

        // Works for all patterns of repeating sections of digits in a number.
        for(int digitsPerSection = 1; digitsPerSection <= digits; ++digitsPerSection) {
            if ((digits % digitsPerSection == 0) && digits != digitsPerSection) {
                // Inside here, the digits are divisble by digitsPerSection.
                int sectionCount = digits / digitsPerSection;
                
                int64_t current_number = i;
                
                bool patternFound = true;
                int64_t currentSection = current_number % magnitude[digitsPerSection];
                for(int64_t section_i = 1; section_i < sectionCount; ++section_i) {

                    current_number /= magnitude[digitsPerSection];

                    int64_t section = current_number % magnitude[digitsPerSection]; 
                    
                    if (currentSection != section) {
                        patternFound = false;
                        break;
                    }
                }

                if (patternFound)
                    return true;
            }
        }

        return false;
    }

    auto part2_first_try() -> std::string {
        std::unordered_set<int64_t> found_numbers;
        auto input = util::get_single_line("input\\input_02.txt");
        char * token;
	    char * cStrToSplit = strdup(input.c_str());
	    token = strtok (cStrToSplit,",");
        int64_t counter = 0;
        while (token != NULL)
        {
            int64_t start = 0;
            int64_t end = 0;
            
            std::string str(token);
            std::string::iterator it = str.begin();

            // find start of range
            while (*it != '-') {
                char c = *it;
                start = start * 10 + (c - '0');
                ++it;
            }
            ++it; // skip the '-'
            // find end of range
            while (it != str.end()) {
                char c = *it;
                end = end * 10 + (c - '0');
                ++it;
            }
            
            for(int64_t i = start; i <= end; ++i) {
                int digits = util::numDigits64bit(i);
                if (!found_numbers.contains(i))
                    if (patternFinder(i, digits)) 
                        found_numbers.insert(i);
            }
            
            token = strtok (NULL, ",");
        }

        for(const auto& number : found_numbers)
            counter += number;

        return std::to_string(counter);
    }
}