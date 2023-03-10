#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest/doctest.h"
#include "../prj.lab/rational/include/rational/rational.h"
#include <iostream>

Rational a(1, 2);
Rational b(2, 3);

Rational sum(7, 6);
Rational diff(-1, 6);
Rational mul(1, 3);


TEST_CASE("checking arithmetic"){
    CHECK((a + b == sum));
    CHECK((a - b == diff));
    CHECK((a * b == mul));
}


