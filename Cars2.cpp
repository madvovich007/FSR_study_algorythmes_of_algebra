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

class Transport {
protected:
    const char * mark;
    int create_year;
public:
    Transport(const char * m, int year): mark(m), create_year(min(year, curr_year)){};
    virtual ~Transport(){};
    virtual int get_cost() const = 0; // сколько стоит
    friend std::ostream & operator<<(std::ostream & out, const Transport & t);
};

class Cars: public Transport{
protected:
    int horse_power;
    char drive; // привод
    int mileage;
public:
    Cars(const char * m, int hp, char d, int mil, int year): Transport(m, year), horse_power(max(hp, 0)), drive(d), mileage(max(mil, 0)){};
    int get_cost() const override{
        return max(horse_power * 10000 - (curr_year - create_year) * 50000 - mileage * 2, min_cost);
    }
    virtual ~Cars(){};
    void set_mileage_roll_back(int c) {
        mileage = max(mileage - c, 0);
    }
};


class Diesel: public Cars {
public:
    Diesel(const char * m, int hp, char d, int mil, int year): Cars(m, hp, d, mil, year) {};
    ~Diesel(){};

    bool can_tow() const{ // можно ли тянуть прицеп
        if (horse_power >= 100 && drive == 'A') {
            return true;
        }
        return false;
    }
    int get_cost() const override {
        return Cars::get_cost() + can_tow() * 100000;
    }
};


class Gas: virtual public Cars {
protected:
    double fuel;
public:
    Gas(const char * m, int hp, char d, int mil, int year, double f): Cars(m, hp, d, mil, year), fuel(max(f, 0)) {};
    int get_cost() const override {
        return Cars::get_cost();
    }
};

class Electric: virtual public Cars{
protected:
    double capacity;
    double battery_charge;
public:
    Electric(const char * m, int hp, char d, int mil, int year, double cap, double b): Cars(m, hp, d, mil, year), capacity(cap), battery_charge(min(max(b, 0), cap)) {};
    ~Electric(){};
    int get_cost() const override {
        return Cars::get_cost() + capacity * 1000;
    }
    double electric_range() const{
        return battery_charge;
    }
};

class Hybrid: public Gas, public Electric {
public:
    Hybrid(const char * m, int hp, char d, int mil, int year, double cap, double b, double f): Cars(m, hp, d, mil, year), Gas(m, hp, d, mil, year, f), Electric(m, hp, d, mil, year, cap, b) {};
    int get_cost() const override {
        return Electric:: get_cost();
    }
};

class Horses: public Transport {
protected:
    int traumated;
public:
    Horses(const char * n, int year, int t): Transport(n, year), traumated(t) {};
    int get_cost() const override {
        return max(10000000 - (curr_year - create_year) * 30000 - traumated * 1000000, 0);
    }
};

class Arabian: virtual public Horses {
public:
    Arabian(const char * n, int year, int t): Horses(n, year, t){};
    int get_cost() const override {
        return Horses::get_cost() + 1500000;
    }
};

class English: virtual public Horses {
public:
    English(const char * n, int year, int t): Horses(n, year, t) {};
    int get_cost() const override {
        return Horses::get_cost() + 800000;
    }
};

class Ahaltekian: virtual public Horses{
public:
    Ahaltekian(const char * n, int year, int t): Horses(n, year, t) {};
    int get_cost() const override {
        return Horses::get_cost() + 2000000;
    }
};

class Running: public Arabian, public English, public Ahaltekian {
public:
    Running(const char * n, int year, int t): Horses(n, year, t), Arabian(n, year, t), English(n, year, t), Ahaltekian(n, year, t) {};
    int get_cost() const override {
        return (Arabian::get_cost() + English::get_cost() + Ahaltekian::get_cost()) / 3;
    }
};

class Scooters: public Transport {
protected:
    int max_speed;
public:
    Scooters(const char * m, int year, int speed): Transport(m, year), max_speed(max(speed, 0)) {};
    int get_cost() const override {
        return max(max_speed * 1000 - (curr_year - create_year) * 1000, 1000);
    }
};

class ElectroScooter: public Scooters {
protected:
    double capacity;
public:
    ElectroScooter(const char * m, int year, int speed, double cap): Scooters(m, year, speed), capacity(max(cap, 0)) {};
    int get_cost() const override {
        return Scooters::get_cost() + capacity * 50;
    }
};

bool operator<(const Cars& c1, const Cars& c2) {
    return c1.get_cost() < c2.get_cost();
}

std::ostream & operator<<(std::ostream &out, const Transport &c){
    out << "(" << c.mark << ", "  << c.create_year << ", " << c.get_cost() << ")";
    return out;
}

class Buyer{
public:
    int total_cost(Transport * all[], int n) {
        int sum = 0;
        for (int i = 0; i < n; i++) {
            std::cout << *all[i] << "\n";
            sum += all[i]->get_cost();
        }
        return sum;
    }
};

int main(void){
    Gas c1("Lada Niva", 83, 'A', 120000, 2015, 40);
    Diesel c2("VW Touareg", 249, 'A', 80000, 2019);
    Gas c3("McLaren 720S", 720, 'R', 15000, 2018, 72);
    Gas c4("GAC Empow", 177, 'F', 10000, 2023, 50);
    Diesel c5("BMW X1", 190, 'A', 60000, 2020);
    Electric c6("Tesla Model 3", 283, 'R', 20000, 2023, 300, 100);
    Hybrid c7("Toyota RAV4", 306, 'A', 30000, 2022, 18, 5, 30);
    Arabian h1("Bublik", 2019, 3);
    English h2("Bulochka", 2021, 0);
    Ahaltekian h3("Dima", 2010, 20);
    Running h4("Oleg", 2020, 1);
    ElectroScooter s1("Yandex_scooter", 2025, 24, 10000);
    ElectroScooter s2("Whoosh_scooter", 2023, 26, 20000);
    Transport * all[] = {&c1, &c2, &c3, &c4, &c5, &c6, &c7, &h1, &h2, &h3, &h4, &s1, &s2};
    int n = 13;
    Buyer buyer;
    int sum = buyer.total_cost(all, n);
    std::cout << "total: " << sum << "\n";

    Cars * car = static_cast<Cars *>(all[1]);
    Diesel * dis = dynamic_cast<Diesel *>(all[1]);
    car->set_mileage_roll_back(50000);
    std::cout << *dis<< " " << dis->can_tow() << "\n";

    Gas * gas = dynamic_cast<Gas *>(all[6]);
    Electric * el = dynamic_cast<Electric *>(gas);
    Horses *hor = dynamic_cast<Horses *>(all[1]);
    std::cout << el->electric_range() << " " << (hor == nullptr) << "\n";
}
