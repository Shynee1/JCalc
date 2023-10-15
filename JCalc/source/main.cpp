#include "jcalc.hpp"
#include <iostream>

using namespace std;

int main() {
    cout << "********** Welcome to Jcalc! **********" << endl;
    string exp;
    while (exp != "stop") {
        cout << "\nEnter your expression: ";
        getline(std::cin, exp);
        cout << jcalc(exp) << endl;
    }
    
}