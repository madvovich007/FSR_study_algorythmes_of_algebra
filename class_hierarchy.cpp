#include <iostream>

#define tol 1e-8
#define curr_year 2026
#define min_cost 50000

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
    if (x < 0.0) {
        return -x;
    }
    return x;
}

class Cars {
protected:
    const char * mark;
    int horse_power;
    char drive; // привод
    int mileage;
    int create_year;
public:
    Cars(): mark(""), horse_power(0), drive('F'), mileage(0), create_year(curr_year) {};
    Cars(const char * m, int hp, char d, int mil, int year): mark(m), horse_power(max(hp, 0)), drive(d), mileage(max(mil, 0)), create_year(min(year, curr_year)){};
    virtual ~Cars(){};
    virtual double charge(double c) {return 0;};// зарядка электрички
    virtual double electric_range() const {return 0;}; // сколько проедет на элетричестве
    friend bool operator<(const Cars& c1, const Cars& c2); // меньше ли стоит
    friend std::ostream & operator<<(std::ostream & out, const Cars& c);
    const char * get_mark() {
        return mark;
    }
    int get_hp() {
        return horse_power;
    }
    char get_drive() {
        return drive;
    }
    int get_mileage() {
        return mileage;
    }
    int get_create_year() {
        return create_year;
    }
    int get_cost() const {
        return max(horse_power * 10000 - (curr_year - create_year) * 50000 - mileage * 2, min_cost);
    }
    void set_mileage_roll_back(int c) {
        mileage = max(mileage - c, 0);
    }
};

class Diesel: public Cars {
public:
    Diesel(): Cars() {};
    Diesel(const char * m, int hp, char d, int mil, int year): Cars(m, hp, d, mil, year) {};
    ~Diesel(){};
    bool can_tow(){ // можно ли тянуть прицеп
        if (horse_power >= 100 && drive == 'A') {
            return true;
        }
        return false;
    }
};

class Hybrid: public Cars {
protected:
    double capacity;
    double battery_charge;
    double fuel;
public:
    Hybrid(): Cars(), capacity(15), battery_charge(0), fuel(0) {};
    Hybrid(const char * m, int hp, char d, int mil, int year, double cap, double b, double f): Cars(m, hp, d, mil, year), capacity(cap), battery_charge(min(max(b, 0), cap)), fuel(max(f, 0)) {};
    ~Hybrid(){};
    double charge(double c) override {
        if (abs(battery_charge - capacity) < tol) {
            return 0;
        }
        double c1 = min(c, capacity - battery_charge);
        battery_charge += c1;
        return c1;
    }
    double electric_range() const override{
        return min(battery_charge, 50);
    }
    double get_battery() {
        return battery_charge;
    }
    double get_fuel() {
        return fuel;
    }
};


class Gas: public Hybrid {
public:
    Gas(): Hybrid("", 0, 'F', 0, curr_year, 0, 0, 0) {};
    Gas(const char * m, int hp, char d, int mil, int year, double f): Hybrid(m, hp, d, mil, year, 0, 0, f) {};
    ~Gas(){};
    double charge(double c) override {
        return 0;
    }
    double electric_range() const override{
        return min(battery_charge, 2);
    }
};

class Electric: public Hybrid {
public:
    Electric(): Hybrid("", 0, 'R', 0, curr_year, 60, 0, 0) {};
    Electric(const char * m, int hp, char d, int mil, int year, double cap, double b): Hybrid(m, hp, d, mil, year, cap, b, 0) {};
    ~Electric(){};
    double electric_range() const override {
        return battery_charge;
    }

};

bool operator<(const Cars& c1, const Cars& c2) {
    return c1.get_cost() < c2.get_cost();
}

std::ostream & operator<<(std::ostream &out, const Cars &c){
    out << "(" << c.mark << ", " << c.horse_power << ", " << c.drive << ", " << c.mileage << ", " << c.create_year << ", " << c.get_cost() << ")";
    return out;
}

int main(void){
    Cars c1("Lada Niva", 83, 'A', 120000, 2015);
    Diesel c2("VW Touareg", 249, 'A', 80000, 2019);
    Gas c3("McLaren 720S", 720, 'R', 15000, 2018, 72);
    Gas c4("GAC Empow", 177, 'F', 10000, 2023, 50);
    Diesel c5("BMW X1", 190, 'A', 60000, 2020);
    Electric c6("Tesla Model 3", 283, 'R', 20000, 2023, 300, 100);
    std::cout << c1 << " " << c2 << " " << c3 << " " << c4 << " " << c5 << " " << c6 << '\n';
    c1.set_mileage_roll_back(50000);
    std::cout << c1 << " " << c1.get_mark() << " " << c1.get_hp() << " " << c1.get_drive() << " " << c1.get_mileage() << " " << c1.get_create_year() << " " << c1.get_cost() << '\n';
    std::cout << (c1 < c2) << " " << (c5 < c4) << " " << (c3 < c6) << '\n';
    std::cout << c2.can_tow() << " " << c5.can_tow() << '\n';
    std::cout << c3.get_fuel() << " " << c3.get_battery() << " " << c4.get_fuel() << " " << c4.get_battery() << '\n';
    std::cout << c1.charge(30) << " " << c2.charge(30) << " " << c3.charge(30) << " " << c4.charge(30) << " " << c5.charge(30) << " " << c6.charge(30) << '\n';
    std::cout << c1.electric_range() << " " << c2.electric_range() << " " << c3.electric_range() << " " << c4.electric_range() << " " << c5.electric_range() << " " << c6.electric_range() << '\n';
}