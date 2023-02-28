#include <iostream>
#include "rational.h"
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest/doctest.h"

Rational a(1, 2);
Rational b(2, 3);

Rational sum(7, 6);
Rational diff(-1, 6);

/*int main(){
    Rational a(1, 2);
    Rational b(2, 3);

    Rational sum(7, 6);
    Rational diff(-1, 6);

    std::cout << (a - b == diff);
}*/


TEST_CASE("checking arithmetic"){
    CHECK(a + b == sum);
    CHECK(a - b == diff);
}


