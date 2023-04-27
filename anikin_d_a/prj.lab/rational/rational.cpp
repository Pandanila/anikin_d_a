#include "prj.lab/rational/include/rational/rational.h"
#include <iostream>
#include <stdexcept>
#include <cstdint>

int32_t gcd(int32_t a, int32_t b){
    int32_t divisor = 0;

    while (a % b != 0 || b % a != 0){
        if (a > b){
            a -= b;
        }
        else{
            b -= a;
        }
    }
    divisor = std::min(a, b);

    return divisor;
}


//input-output
inline std::istream& operator>>(std::istream& istrm, Rational& rhs){
    return rhs.ReadFrom(istrm);
};
inline std::ostream& operator<<(std::ostream& ostrm, Rational& rhs){
    return rhs.WriteTo(ostrm);
};

Rational::Rational(const int32_t in_num, const int32_t in_denum){
    if (in_denum == 0){
        throw std::invalid_argument("division by zero");
    }

    int32_t d = gcd(in_num, in_denum);

    num = in_num / d;
    denum = in_denum / d;

    if (denum < 0){
        denum = - denum;
        num = - num;
    }
}

Rational::Rational(const int32_t in_num) noexcept{
    num = in_num;
    denum = 1;
};

std::istream& Rational::ReadFrom(std::istream& istrm){
    char slash = 0;
    int32_t in_num = 0;
    int32_t in_denum = 1;
    istrm >> in_num >> slash >> in_denum;
    if (istrm.good() || !istrm.fail() && istrm.eof()){
        if (slash == Rational::separator){
            istrm.clear();
            *this = Rational(in_num, in_denum);
        }
        else{
            istrm.setstate(std::ios_base::failbit);
        }
    }
    return istrm;
}

std::ostream& Rational::WriteTo(std::ostream& ostrm) const{
    ostrm << num << separator << denum;
    return ostrm;
}

Rational& Rational::operator+=(Rational& rhs) {
    *this = Rational(num += rhs.num, denum += rhs.denum);
    return *this;
}

Rational& Rational::operator-=(Rational& rhs) {
    *this = Rational(num -= rhs.num, denum -= rhs.denum);
    return *this;
}

Rational& Rational::operator*=(const Rational& rhs) {
    *this = Rational(num *= rhs.num, denum *= rhs.denum);
    return *this;
}

Rational& Rational::operator/=(const Rational& rhs){
    *this = Rational(num /= rhs.num, denum /= rhs.denum);
    return *this;
}

bool Rational::operator==(const Rational& rhs) const {
    return (num == rhs.num) && (denum == rhs.denum);
}

bool Rational::operator!=(const Rational& rhs) const {
    return (num != rhs.num) || (denum != rhs.denum);
}

bool Rational::operator>(const Rational &rhs) const{
    return (num * rhs.denum - denum * rhs.num) > 0;
};

bool Rational::operator<(const Rational &rhs) const{
    return (num * rhs.denum - denum * rhs.num) > 0;
}

bool Rational::operator>=(const Rational &rhs) const{
    return (num * rhs.denum - denum * rhs.num) >= 0;
}

bool Rational::operator<=(const Rational &rhs) const{
    return (num * rhs.denum - denum * rhs.num) >= 0;
}

Rational& Rational::operator-() {
    num = -num;
    return *this;
}

Rational& operator+(Rational& lhs, Rational& rhs){
    lhs += rhs;
    return lhs;
}

Rational& operator-(Rational& lhs, Rational& rhs){
    lhs -= rhs;
    return lhs;
}

Rational& operator*(Rational& lhs, Rational& rhs){
    lhs *= rhs;
    return lhs;
}

Rational& operator/(Rational& lhs, Rational& rhs){
    lhs /= rhs;
    return lhs;
}
