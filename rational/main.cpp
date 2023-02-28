#include <istream>
#include <ostream>
#include <iostream>
#include "rational.h"

int main() {
    Rational num_1 = Rational();
    Rational num_2 = Rational();
    std::cin >> num_1;
    std::cin >> num_2;
    std::cout << (num_1 + num_2);
}

