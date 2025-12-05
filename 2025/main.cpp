#include "incl.h"
#include "01.h"
#include "02.h"

int main(int argc, char** args) {
    util::Timer timer;
    std::string answer;
    timer.start();
    answer = d02::part2_first_try();
    
    timer.stop();
    std::cout << answer << std::endl;
    timer.print_all();

    return 0;
}