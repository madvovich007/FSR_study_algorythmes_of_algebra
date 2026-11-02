#include <iostream>

#define tol 1e-8
#define MAX_colour 255

double max(double a, double b) {
    if (a > b) {
        return a;
    }
    return b;
}

double min(double a, double b) {
    if (a < b) {
        return a;
    }
    return b;
}

double abs(double x) {
    if (x < -tol) {
        return -x;
    }
    return x;
}

class Colour {
protected:
    double x;
    double y;
    double z;
    double w;
public:
    Colour(): x(0), y(0), z(0), w(0) {};
    virtual ~Colour(){};
    Colour(double r, double g, double b, double w): x(min(max(r, 0), MAX_colour)), y(min(max(g, 0), MAX_colour)), z(min(max(b, 0), MAX_colour)), w(min(max(0, w), 1)) {};
    friend Colour operator+(const Colour& c1, const Colour& c2);
    friend std::ostream & operator<<(std::ostream & out, const Colour& c);
    virtual bool is_black() const{return false;};
    virtual bool is_clear() const{return false;};
};

class RGB: public Colour {
public:
    RGB(): Colour(0,0,0,1) {};
    RGB(double r, double g, double b, double w): Colour(r, g, b, w) {};
    ~RGB(){};
    bool is_black() const override{
        if (x < tol && y < tol && z < tol && abs(w -1) < tol){
            return true;
        }
        return false;
    }
    double get_red(RGB &c) {
        return x;
    }

    double get_green(RGB &c) {
        return y;
    }

    double get_blue(RGB &c) {
        return z;
    }

    double get_alpha(RGB &c) {
        return w;
    }
    void set_red(double c) {
        x = c;
    }

    void set_green(double c) {
        y = c;
    }

    void set_blue(double c) {
        z = c;
    }

    void set_alpha(double c) {
        w = c;
    }
};

class CMYK: public Colour {
public:
    CMYK(): Colour(0, 0, 0, 0) {};
    CMYK(double x, double y, double z, double w):  Colour(x, y, z, w){};
    ~CMYK() {};
    bool is_black() const override {
        if (abs(w - 1) < tol){
            return true;
        }
        return false;
    }
    double get_cyan(CMYK &c) {
        return x;
    }

    double get_magenta(CMYK &c) {
        return y;
    }

    double get_yellow(CMYK &c) {
        return z;
    }

    double get_black(CMYK &c) {
        return w;
    }

    void set_cyan(double c) {
        x = c;
    }

    void set_magenta(double c) {
        y = c;
    }

    void set_yellow(double c) {
        z = c;
    }

    void set_black(double c) {
        w = c;
    }
};

class warm_CMYK:public Colour {
public:
    warm_CMYK(): Colour(0, 0, 0, 0) {};
    warm_CMYK(double x, double y, double z, double w): Colour(x, y, z, w) {};
    ~warm_CMYK() {};
    bool is_clear() const override{
        if (!(is_black()) && abs(w) < tol) {
            if (abs(x) < tol && abs(y) < tol && abs(z) > tol) {
                return true;
            }
            if (abs(x) > tol && abs(y) < tol && abs(z) < tol){
                return true;
            }
            if (abs(x) < tol && abs(y) > tol && abs(z) < tol){
                return true;
            }
            if (abs(x - y) < tol && abs(z) < tol && abs(x) > tol) {
                return true;
            }
            if (abs(x - z) < tol && abs(y) < tol && abs(x) > tol) {
                return true;
            }
            if (abs(y - z) < tol && abs(x) < tol && abs(y) > tol) {
                return true;
            }
        }
        return false;
    }
};



Colour operator+(const Colour& c1, const Colour& c2) {
    return Colour(min(c1.x + c2.x, MAX_colour), min(c1.y + c2.y, MAX_colour), min(c1.z + c2.z, MAX_colour), min(c1.w + c2.w, 1.0));
}

std::ostream & operator<<(std::ostream &out, const Colour &c){
    out << "(" << c.x << ", " << c.y << ", " << c.z << ")";
    return out;
}

int main() {
    Colour c1(0.1, 0.2, 0.3, 0.1);
    RGB c2(0.2, 0.3, 0.4, 0.5);
    CMYK c3(0.4, 0.5, 0.6, 0.8);
    warm_CMYK c4(0.6, 0.7, 0.8, 0.9);
    std::cout << c1 << " " << c2 << " " << c3 << " " << c4 << '\n';
}
