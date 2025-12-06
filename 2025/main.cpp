#include "incl.h"
#include "01.h"
#include "02.h"
#include "03.h"

int main(int argc, char** args) {
    util::Timer timer;
    std::string answer;
    timer.start();
    answer = d03::part2_first_try();
    timer.stop();
    std::cout << answer << std::endl;
    timer.print_all();

    return 0;
}