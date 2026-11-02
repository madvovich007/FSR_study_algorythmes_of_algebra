#include <iostream>

#define MAX_colour 255

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
class fraction ;
class Colour {
private:
    int red;
    int green;
    int blue;
public:
    Colour(): red(0), green(0), blue(0) {};
    ~Colour();
    Colour(int rgb):red(min(max(rgb, 0), MAX_colour)), green(min(max(rgb, 0), MAX_colour)), blue(min(max(rgb, 0), MAX_colour)) {}
    Colour(int r, int g, int b): red(min(max(r, 0), MAX_colour)), green(min(max(g, 0), MAX_colour)), blue(min(max(b, 0), MAX_colour)) {}
    friend Colour operator+(Colour& c1, Colour& c2);
    friend Colour operator-(Colour& c1, Colour& c2);
    friend Colour operator+(Colour& c1, int c2);
    friend Colour operator-(Colour& c1, int c2);
    friend Colour operator*(int coefficient, Colour& c1);
    friend Colour operator-(Colour& c1);
    friend std::ostream & operator<<(std::ostream & out, const Colour& c);
    friend std::istream & operator>>(std::istream & in, Colour& c);

    friend Colour operator*(Colour & c, fraction & f);
    friend Colour operator*(fraction & f, Colour & c);

    operator double();
    operator bool();
};

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
    friend fraction operator*(fraction& c1, fraction& c2);
    friend fraction operator-(fraction& c1);
    friend std::ostream & operator<<(std::ostream & out, const fraction& c);
    friend std::istream & operator>>(std::istream & in, fraction& c);

    friend Colour operator*(Colour& c, fraction& f);
    friend Colour operator*(fraction& f, Colour& c);

    operator double();
    operator bool();
};

Colour::~Colour() {};

Colour operator+(Colour& c1, Colour& c2) {
    return Colour(min(c1.red + c2.red, MAX_colour), min(c1.green + c2.green, MAX_colour), min(c1.blue + c2.blue, MAX_colour));
}
Colour operator-(Colour& c1, Colour& c2) {
    return Colour(max(c1.red - c2.red, 0), max(c1.green - c2.green, 0), max(c1.blue - c2.blue, 0));
}

Colour operator + (Colour& c1, int c2) {
    return Colour(max(c1.red + c2, 0), max(c1.green + c2, 0), max(c1.blue + c2, 0));
}

Colour operator-(Colour& c1, int c2) {
    return Colour(max(c1.red - c2, 0), max(c1.green - c2, 0), max(c1.blue - c2, 0));
}

Colour operator*(int coefficient, Colour& c1) {
    return Colour(c1.red * coefficient, c1.green * coefficient, c1.blue * coefficient);
}

fraction operator*(fraction& c1, fraction& c2) {
    return fraction(c1.numerator * c2.numerator, c1.denominator * c2.denominator);
}

Colour operator-(Colour& c1) {
    return Colour(255 - c1.red, 255 - c1.green, 255 - c1.blue);
}

std::ostream & operator<<(std::ostream &out, const Colour &c){
    out << "(" << c.red << ", " << c.green << ", " << c.blue << ")";
    return out;
}

std::istream & operator>>(std::istream & in, Colour& c){
    in >> c.red >> c.green >> c.blue;
    return in;
}

Colour::operator double() {
    return (red + green + blue) / (MAX_colour * 3.0) ;
}
// полностью ли черный
Colour::operator bool(){
    if (red == 0 && green == 0 && blue == 0){
        return 0;
    }
    return 1;
}

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
    return numerator * 1.0 / denominator ;
}
//меньше ли 1
fraction::operator bool(){
    if (numerator < denominator) {
        return 0;
    }
    return 1;
}

Colour operator*(Colour& c, fraction & f) {
    if (f.denominator == 0) {
        return Colour();
    }
    return Colour(c.red * f.numerator / f.denominator, c.green * f.numerator / f.denominator, c.blue * f.numerator / f.denominator);
}

Colour operator*(fraction & f, Colour & c){
    return c * f;
}

int main() {
    fraction fraction1(1, 2);
    Colour colour1(100, 101, 104);
    std::cout << colour1 * fraction1 << ", " << fraction1 * colour1 << '\n';
}

