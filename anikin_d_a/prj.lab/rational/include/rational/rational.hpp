//
// Created by danan on 28.02.2023.
//

#ifndef RATIONAL_RATIONAL_H
#define RATIONAL_RATIONAL_H

int32_t gcd(int32_t a, int32_t b);
class Rational{
private:
    int32_t num{0};
    int32_t denum{1};
    static const char separator = '/';
public:
    Rational() = default;
    Rational(const Rational&) = default;
    Rational(int32_t in_num, int32_t in_denum);
    ~Rational() = default;

    Rational& operator+=(Rational& rhs);
    Rational& operator-=(Rational& rhs);
    Rational& operator*=(const Rational& rhs);
    Rational& operator/=(const Rational& rhs);
    bool operator==(const Rational& rhs) const;
    bool operator!=(const Rational &rhs) const;
    bool operator>(const Rational &rhs) const;
    bool operator<(const Rational &rhs) const;
    bool operator>=(const Rational &rhs) const;
    bool operator<=(const Rational &rhs) const;
    Rational& operator-();

    std::istream& ReadFrom(std::istream& istrm);
    std::ostream& WriteTo(std::ostream& ostrm) const;
};

inline std::istream& operator>>(std::istream& istrm, Rational& rhs);
inline std::ostream& operator<<(std::ostream& ostrm, Rational& rhs);

//Algebra
Rational& operator+(Rational& lhs, Rational& rhs);
Rational& operator-(Rational& lhs, Rational& rhs);
Rational& operator*(Rational& lhs, Rational& rhs);
Rational& operator/(Rational& lhs, Rational& rhs);



#endif //RATIONAL_RATIONAL_H
