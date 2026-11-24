#include <iostream>
#include <cstring>


class Duration {
private:
    int days;
    char str_buf[32];
public:
    Duration();
    Duration(int d);

    operator int() const;
    operator const char*() const;

    Duration operator-();
    Duration operator+(const Duration& dur) const;
    Duration operator-(const Duration& dur) const;
    Duration operator*(int k) const;
    friend ostream& operator<<(ostream& out, const Duration& d);
    friend istream& operator>>(istream& in, Duration& d);
};

class Date {
private:
    int day, month, year;
    char str_buf[32];

public:
    static bool is_leap(int y);
    int to_days() const;
    void from_days(int total);

    Date();
    Date(int d, int m, int y);

    operator int() const;
    operator const char*() const;

    const Date& operator++();
    friend Date operator+(const Date& d, const Duration& dur);
    friend Date operator-(const Date& d, const Duration& dur);
    friend Duration operator-(const Date& d1, const Date& d2);
    friend ostream& operator<<(ostream& out, const Date& d);
    friend istream& operator>>(istream& in, Date& d);
};
Duration::Duration() : days(0) {}
Duration::Duration(int d) : days(d) {}

Duration::operator int() const {
    return days;
}
Duration::operator const char*() const {
    sprintf((char*)str_buf, "%d days", days);
    return str_buf;
}

Duration Duration::operator-() {
    return Duration(-days);
}
Duration Duration::operator+(const Duration& dur) const {
    return Duration(days + dur.days);
}
Duration Duration::operator-(const Duration& dur) const {
    return Duration(days - dur.days);
}
Duration Duration::operator*(int k) const {
    return Duration(days * k);
}
ostream& operator<<(ostream& out, const Duration& d) {
    out << d.days << " days";
    return out;
}
istream& operator>>(istream& in, Duration& d) {
    in >> d.days;
    return in;
}



bool Date::is_leap(int y) {
    return ((y % 4 == 0 && y % 100 != 0) || (y % 400 == 0));
}
int Date::to_days() const {
    int days = 0;
    for (int y = 2000; y < year; y++)
        days += is_leap(y) ? 366 : 365;
    int mdays[] = {31, 28 + is_leap(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    for (int m = 0; m < month - 1; m++)
        days += mdays[m];
    days += day - 1;
    return days;
}
void Date::from_days(int total) {
    year = 2000;
    int fl1 = 1;
    while (fl1) {
        int yd = is_leap(year) ? 366 : 365;
        if (total < yd) fl1 = 0;
        else {
            total -= yd;
            year++;
        }
    }
    int fl2 = 1;
    int mdays[] = {31, 28 + is_leap(year), 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    month = 1;
    for (int m = 0; m < 12 && fl2; m++) {
        if (total < mdays[m]) fl2 = 0;
        else {
            total -= mdays[m];
            month++;
        }
    }
    day = total + 1;
}

Date::Date() : day(1), month(1), year(2000) {}
Date::Date(int d, int m, int y) : day(d), month(m), year(y) {}

Date::operator int() const {
    return to_days();
}
Date::operator const char*() const {
    sprintf((char*)str_buf, "%02d.%02d.%04d", day, month, year);
    return str_buf;
}
const Date& Date::operator++() {
    from_days(to_days() + 1);
    return *this;
}
Date operator+(const Date& d, const Duration& dur) {
    Date res = d;
    res.from_days(d.to_days() + (int)dur);
    return res;
}
Date operator-(const Date& d, const Duration& dur) {
    Date res = d;
    res.from_days(d.to_days() - (int)dur);
    return res;
}
Duration operator-(const Date& d1, const Date& d2) {
    return Duration((int)d1 - (int)d2);
}
ostream& operator<<(ostream& out, const Date& d) {
    out << d.day << "." << d.month << "." << d.year;
    return out;
}
istream& operator>>(istream& in, Date& d) {
    char dot;
    in >> d.day >> dot >> d.month >> dot >> d.year;
    return in;
}

int main() {
    Duration d2(10);
    cout << "Tests for Duration: " << endl;
    int days_int = d2;
    const char* days_str = d2;
    cout << "d2 as int:    " << days_int << endl;
    cout << "d2 as char*:  " << days_str << endl;
    Duration d3 = -d2;              
    cout << "Unary minus -d2: " << d3 << endl;
    cout << "Binary operations: " << endl;
    Duration d4(5);
    Duration sum = d2 + d4;
    Duration diff = d2 - d4;
    Duration mul = d2 * 3;
    cout << "10 + 5 = " << sum << endl;
    cout << "10 - 5 = " << diff << endl;
    cout << "10 * 3 = " << mul << endl;
    cout << "Operator<< for d2: " << d2 << endl;
    cout << "Input duration: ";
    Duration d_input;
    cin >> d_input;
    cout << "You chose: " << d_input << endl;


    Date date2(31, 10, 2026);
    cout << "Tests for Date" << endl;
    int date_int = date2; 
    const char* date_str = date2;
    cout << "date2 as int:    " << date_int << " (days from 01.01.2000)" << endl;
    cout << "date2 as char*:  " << date_str << endl;
    Date date3(31, 10, 2026);
    cout << "Before ++: " << date3 << endl;
    ++date3;
    cout << "After ++: " << date3 << endl;
    Date date3b(28, 2, 2024);
    cout << "Before ++: " << date3b << " (leap year)" << endl;
    ++date3b;
    cout << "After ++: " << date3b << endl;
    Date date3c(31, 12, 2026);
    cout << "Before ++: " << date3c << endl;
    ++date3c;
    cout << "After ++: " << date3c << endl;
    cout << "Binary operations: " << endl;
    Date d_a(15, 10, 2026);
    Date d_b(25, 10, 2026);
    Duration dur(10);
    Date d_plus = d_a + dur; 
    Date d_minus = d_b - dur;
    Duration d_diff = d_b - d_a;
    cout << d_a << " + " << dur << " = " << d_plus << endl;
    cout << d_b << " - " << dur << " = " << d_minus << endl;
    cout << d_b << " - " << d_a << " = " << d_diff << endl;
    Duration d_diff2 = d_a - d_b;
    cout << d_a << " - " << d_b << " = " << d_diff2 << endl;
    cout << "Operator<< for date2: " << date2 << endl;
    cout << "Input date in format DD.MM.YYYY: ";
    Date date_input;
    cin >> date_input;
    cout << "You chose " << date_input << endl;
    return 0;
}