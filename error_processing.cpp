#include <iostream>
#include <fstream>

class Legendre_error {
protected:
    const char * msg;
public:
    Legendre_error(const char * m): msg(m){};
    const char * type_err() {
        return msg;
    };
};
class Point_error: public Legendre_error {
private:
    double x;
public:
    Point_error(double x1): Legendre_error("Point not in range"), x(x1){};
    double get_point() {
        return x;
    };
};

class Power_error: public Legendre_error {
private:
    int n;
public:
    Power_error(int n1): Legendre_error("Low Power"), n(n1){};
    int get_n() {
        return n;
    }
};

class big_Power_error: public Legendre_error {
private:
    int n;
public:
    big_Power_error(int n1): Legendre_error("too big Power"), n(n1){};
    int get_n() {
        return n;
    }
};

class Legendre{
private:
    double x;
    double polynom[1000];
    int poly_size;
public:
    Legendre(double x0): x(x0), poly_size(0) {
        if (x0 < -1 || x0 > 1) {
            throw Point_error(x0);
        }
        polynom[0] = 1;
        polynom[1] = x0;
        poly_size = 2;
    };
    double calculate(int n) {
        if (n < 0) {
            throw Power_error(n);
        }
        if (n >= 1000) {
            throw big_Power_error(n);
        }
        if (n < poly_size) {
            return polynom[n];
        }
        double p1 = calculate(n-1);
        double p2 = calculate(n-2);
        double p_new = (2 * n - 1) * x * p1 / n - (n - 1) * p2 / n;
        polynom[poly_size] = p_new;
        poly_size++;
        return p_new;
    }
};

class Input_err: public Legendre_error {
public:
    Input_err(const char* str) : Legendre_error(str){};
};

class NotFound_err: public Legendre_error {
public:
    NotFound_err(const char* str) : Legendre_error(str){};
};

int main(void) {
    std::ifstream infile("Input.txt");
    if (!infile.is_open()) {
        try {
            throw NotFound_err("File input not found");
        }
        catch (NotFound_err & err) {
            std::cerr << err.type_err() << '\n';
            return 0;
        }
    }
    std::ofstream outfile("output.txt");
    if (!outfile.is_open()) {
        try {
            throw NotFound_err("File output not found");
        }
        catch (NotFound_err & err) {
            std::cerr << err.type_err() << '\n';
            infile.close();
            return 0;
        }
    }
    int flag = 1;
    double x;
    int n;
    while (flag) {
        if (!(infile >> x >> n)) {
            if (infile.eof()) {
                flag = 0;
            }
            else {
                try {
                    throw Input_err("Incorrect dataset");
                }
                catch (Input_err & err) {
                    std::cout << err.type_err() << '\n';
                }
                infile.clear();
            }
        }
        else {
            try {
                Legendre c(x);
                double res = c.calculate(n);
                outfile << "P" << n << " (" << x << ") = " << res << '\n';
            }
            catch (Power_error & err) {
                outfile << err.get_n() << ": " << err.type_err() << '\n';
            }
            catch (Point_error & err) {
                outfile << err.get_point() << ": " << err.type_err() << '\n';
            }
            catch (big_Power_error & err) {
                outfile << err.get_n() << ": " << err.type_err() << '\n';
            }
        }
    }
    infile.close();
    outfile.close();
    return 0;
}