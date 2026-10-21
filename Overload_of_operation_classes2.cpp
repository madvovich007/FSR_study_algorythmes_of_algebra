#include <iostream>

#define MAX_fraction 255

class fraction;

int max(int a, int b) {
    if (a > b) {
        return a;
    }
    return b;
}

int min(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

class fraction{
private:
    int numerator;
    int denominator;
public:
    fraction(): numerator(0), denominator(1) {};
    ~fraction();
    fraction(int c):numerator(c), denominator(1) {};
    fraction(int a, int b): numerator(a), denominator(b) {};
    friend fraction operator+(fraction& c1, fraction& c2);
    friend fraction operator-(fraction& c1, fraction& c2);
    friend fraction operator+(fraction& c1, int c2);
    friend fraction operator-(fraction& c1, int c2);
    friend fraction operator*(fraction& c1, int coefficient);
    friend fraction operator-(fraction& c1);
    friend std::ostream & operator<<(std::ostream & out, const fraction& c);
    friend std::istream & operator>>(std::istream & in, fraction& c);
    operator double();
    operator bool();
};

fraction::~fraction() {};

fraction operator+(fraction& c1, fraction& c2) {
    return fraction(c1.numerator * c2.denominator + c1.denominator * c2.numerator, c1.denominator * c2.denominator);
}
fraction operator-(fraction& c1, fraction& c2) {
    return fraction(c1.numerator * c2.denominator - c1.denominator * c2.numerator, c1.denominator * c2.denominator);
}

fraction operator + (fraction& c1, int c2) {
    return fraction(c1.numerator + c2 * c1.denominator, c1.denominator);
}

fraction operator-(fraction& c1, int c2) {
    return fraction(c1.numerator - c2 * c1.denominator, c1.denominator);
}

fraction operator*(fraction& c1, int coefficient) {
    return fraction(c1.numerator *  coefficient, c1.denominator);
}

fraction operator-(fraction& c1) {
    return fraction(- c1.numerator, c1.denominator);
}

std::ostream & operator<<(std::ostream &out, const fraction &c){
    out << "(" << c.numerator << "/ " << c.denominator << ")";
    return out;
}

std::istream & operator>>(std::istream & in, fraction& c){
    in >> c.numerator >> c.denominator;
    return in;
}

fraction::operator double() {
    return numerator / denominator ;
}
//меньше ли 1
fraction::operator bool(){
    if (numerator < denominator) {
        return 0;
    }
    return 1;
}

int main() {
    fraction fraction1(100, 101);
    fraction fraction2(102, 101);
    std::cout << fraction1 + fraction2 << ',' << fraction1 - fraction2 << '\n';
    std::cout << (double)fraction1 << '\n';
    std::cout << (bool)fraction2 << '\n';
}

