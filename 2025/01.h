#pragma once
#include "incl.h"

namespace d01 {

    
    const int LEFT = 76;
    const int RIGHT = 82;

    auto part1_first_try() -> std::string {
        int dial_number = 50;
        int zero_counter = 0;
        auto lines = util::get_lines("input\\input_01.txt");

        for(const auto& l : lines) {
            char direction = l[0];
            
            std::size_t start = 1;
            std::size_t end = l.length() - 1;
            std::string s = l.substr(start, end);
            int dialAmount = std::stoi(s);
            std::cout << "Start: " << dial_number << " ";
            switch (direction) {
                case LEFT:
                    std::cout << "turn left by " << dialAmount << ".";
                    dial_number -= dialAmount;
                    if (dial_number < 0) {
                        dial_number %= 100;
                        dial_number = 100 + dial_number;
                    }
                    if (dial_number == 100)
                        dial_number = 0;
                    break;
                case RIGHT:
                    std::cout << "turn right by " << dialAmount << ".";
                    dial_number += dialAmount;
                    if (dial_number >= 100) {
                        dial_number %= 100;
                    }
                    if (dial_number == 100)
                        dial_number = 0;
                    break;
                default:
                    throw;
                    break;
            }

            std::cout << " Result: " << dial_number;
            if (dial_number == 100)
                std::cout << "ALAAAAAAAAAAAAAAAAAAARM";
            
            std::cout << std::endl;

            if (dial_number == 0)
                ++zero_counter;
                
        }

        return std::to_string(zero_counter);
    }

    /// @brief Removed output debugging strings.
    /// @return 
    auto part1_op_01() -> std::string {
        int dial_number = 50;
        int zero_counter = 0;
        auto lines = util::get_lines("input\\input_01.txt");

        for(const auto& l : lines) {
            char direction = l[0];
            
            std::size_t start = 1;
            std::size_t end = l.length() - 1;
            std::string s = l.substr(start, end);
            int dialAmount = std::stoi(s);
            switch (direction) {
                case LEFT:
                    dial_number -= dialAmount;
                    if (dial_number < 0) {
                        dial_number %= 100;
                        dial_number = 100 + dial_number;
                    }
                    if (dial_number == 100)
                        dial_number = 0;
                    break;
                case RIGHT:
                    dial_number += dialAmount;
                    if (dial_number >= 100) {
                        dial_number %= 100;
                    }
                    if (dial_number == 100)
                        dial_number = 0;
                    break;
                default:
                    throw;
                    break;
            }

            if (dial_number == 0)
                ++zero_counter;
        }

        return std::to_string(zero_counter);
    }

    /// @brief Optimized parsing.
    /// @return 
    auto part1_op_02() -> std::string {
        int dial_number = 50;
        int zero_counter = 0;
        auto lines = util::get_lines("input\\input_01.txt");

        for(const auto& l : lines) {
            char direction = l[0];
            
            int dialAmount = 0;
            for (std::size_t i = 1; i < l.size(); ++i) {
                char c = l[i];
                if (c < '0' || c > '9') {
                    throw;
                }
                dialAmount = dialAmount * 10 + (c - '0');
            }

            switch (direction) {
                case LEFT:
                    dial_number -= dialAmount;
                    if (dial_number < 0) {
                        dial_number %= 100;
                        dial_number = 100 + dial_number;
                    }
                    if (dial_number == 100)
                        dial_number = 0;
                    break;
                case RIGHT:
                    dial_number += dialAmount;
                    dial_number %= 100;

                    if (dial_number >= 100)
                        dial_number %= 100;
                        
                    if (dial_number == 100)
                        dial_number = 0;
                    break;
                default:
                    throw;
                    break;
            }

            if (dial_number == 0)
                ++zero_counter;
        }

        return std::to_string(zero_counter);
    }

    /// @brief 
    /// @return 
    auto part1_op_03() -> std::string {
        int dial_number = 50;
        int zero_counter = 0;
        auto lines = util::get_lines("input\\input_01.txt");

        for(const auto& l : lines) {
            char direction = l[0];
            
            int dialAmount = 0;
            for (std::size_t i = 1; i < l.size(); ++i) {
                char c = l[i];
                if (c < '0' || c > '9') {
                    throw;
                }
                dialAmount = dialAmount * 10 + (c - '0');
            }

            switch (direction) {
                case LEFT:
                    dial_number -= dialAmount;
                    if (dial_number < 0)
                    {
                        // Because we have to do an if check anyway, we can get away with only doing the modulo operation when the check goes through.
                        dial_number %= 100;
                        dial_number = 100 + dial_number;
                    }
                    
                    break;
                case RIGHT:
                    dial_number += dialAmount;
                    // Cheaper to do this anyway than to check if if we need to do this, and then also do it during the cases where we do.
                    dial_number %= 100;
                        
                    break;
                default:
                    throw;
                    break;
            }

            if (dial_number == 100)
                dial_number = 0;

            if (dial_number == 0)
                ++zero_counter;
        }

        return std::to_string(zero_counter);
    }

    auto part2_first_try() -> std::string {
        int dial_number = 50;
        int new_dial_number = 0;
        int zero_counter = 0;
        auto lines = util::get_lines("input\\input_01.txt");

        for(const auto& l : lines) {
            char direction = l[0];
            std::size_t start = 1;
            std::size_t end = l.length() - 1;
            std::string s = l.substr(start, end);
            int dialAmount = std::stoi(s);
            std::cout << "Start: " << dial_number << " ";
            int extra_clicks_at_zero = 0;
            int true_dial_amount = 0;
            switch (direction) {
                case LEFT:
                    std::cout << "turn left by " << dialAmount << ".";
                    true_dial_amount = dialAmount % 100;
                    extra_clicks_at_zero = dialAmount / 100;
                    new_dial_number = dial_number - true_dial_amount ;

                    if (new_dial_number < 0) {
                        extra_clicks_at_zero += dial_number != 0 ? 1 : 0;
                        new_dial_number %= 100;
                        new_dial_number = 100 + new_dial_number;
                    }

                    if (new_dial_number == 100) {
                        new_dial_number = 0;
                    }
                    break;
                case RIGHT:
                    std::cout << "turn right by " << dialAmount << ".";
                    
                    true_dial_amount = dialAmount % 100;
                    extra_clicks_at_zero = dialAmount / 100;
                    new_dial_number = dial_number + true_dial_amount;

                    if (new_dial_number > 100) {
                        extra_clicks_at_zero += 1;
                        new_dial_number %= 100;
                    }
                    else if (new_dial_number == 100)
                        new_dial_number = 0;

                    break;
                default:
                    throw;
                    break;
            }
            
            dial_number = new_dial_number;

            std::cout << " Result: " << dial_number;

            if (extra_clicks_at_zero > 0)
                std::cout << " extra clicks: " << extra_clicks_at_zero << ". ";
            
            std::cout << std::endl;

            if (dial_number == 0)
                ++zero_counter;
            
            zero_counter += extra_clicks_at_zero;
                
        }

        return std::to_string(zero_counter);
    }

    auto part2_op_01() -> std::string {
        int dial_number = 50;
        int new_dial_number = 0;
        int zero_counter = 0;
        auto lines = util::get_lines("input\\input_01.txt");

        for(const auto& l : lines) {
            char direction = l[0];
            std::size_t start = 1;
            std::size_t end = l.length() - 1;
            std::string s = l.substr(start, end);
            int dialAmount = std::stoi(s);
            int extra_clicks_at_zero = 0;
            int true_dial_amount = 0;
            switch (direction) {
                case LEFT:
                    true_dial_amount = dialAmount % 100;
                    extra_clicks_at_zero = dialAmount / 100;
                    new_dial_number = dial_number - true_dial_amount ;

                    if (new_dial_number < 0) {
                        extra_clicks_at_zero += dial_number != 0 ? 1 : 0;
                        new_dial_number %= 100;
                        new_dial_number = 100 + new_dial_number;
                    }

                    if (new_dial_number == 100) {
                        new_dial_number = 0;
                    }
                    break;
                case RIGHT:
                    
                    true_dial_amount = dialAmount % 100;
                    extra_clicks_at_zero = dialAmount / 100;
                    new_dial_number = dial_number + true_dial_amount;

                    if (new_dial_number > 100) {
                        extra_clicks_at_zero += 1;
                        new_dial_number %= 100;
                    }
                    else if (new_dial_number == 100)
                        new_dial_number = 0;

                    break;
                default:
                    throw;
                    break;
            }
            
            dial_number = new_dial_number;

            if (dial_number == 0)
                ++zero_counter;
            
            zero_counter += extra_clicks_at_zero;
                
        }

        return std::to_string(zero_counter);
    }

    auto part2_op_02() -> std::string {
        int dial_number = 50;
        int new_dial_number = 0;
        int zero_counter = 0;
        auto lines = util::get_lines("input\\input_01.txt");

        for(const auto& l : lines) {
            char direction = l[0];
            int dialAmount = 0;
            for (std::size_t i = 1; i < l.size(); ++i) {
                char c = l[i];
                if (c < '0' || c > '9') {
                    throw;
                }
                dialAmount = dialAmount * 10 + (c - '0');
            }
            int extra_clicks_at_zero = 0;
            switch (direction) {
                case LEFT:
                    extra_clicks_at_zero = dialAmount / 100;
                    new_dial_number = dial_number - dialAmount % 100;

                    if (new_dial_number < 0) {
                        extra_clicks_at_zero += dial_number != 0 ? 1 : 0;
                        new_dial_number %= 100;
                        new_dial_number = 100 + new_dial_number;
                    }

                    break;
                case RIGHT:
                    extra_clicks_at_zero = dialAmount / 100;
                    new_dial_number = dial_number + dialAmount % 100;

                    if (new_dial_number > 100) {
                        extra_clicks_at_zero += 1;
                        new_dial_number %= 100;
                    }

                    break;
                default:
                    throw;
                    break;
            }
            
            if (new_dial_number == 100)
                new_dial_number = 0;

            dial_number = new_dial_number;

            if (dial_number == 0)
                ++zero_counter;
            
            zero_counter += extra_clicks_at_zero;
                
        }

        return std::to_string(zero_counter);
    }
}