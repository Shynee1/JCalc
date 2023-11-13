#include "jcalc.hpp"
#include <iostream>
#include <stdio.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        std::cerr << "Usage: jcalc <expression>" << std::endl;
        return 1;
    }

    std::string commandLineStr = "";
    for (int i = 1; i < argc; i++) 
        commandLineStr.append(argv[i]).append(" ");

    std::cout << jcalc(commandLineStr) << std::endl;

    return 0;
}