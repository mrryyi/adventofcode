#include "incl.h"
#include "01.h"
#include "02.h"
#include "03.h"
#include "04.h"
#include "05.h"
#include "06.h"
#include "07.h"

int main(int argc, char** args) {
    util::Timer timer;
    std::string answer;
    timer.start();
    answer = d07::p1();
    timer.stop();
    std::cout << answer << std::endl;
    timer.print_all();

    return 0;
}