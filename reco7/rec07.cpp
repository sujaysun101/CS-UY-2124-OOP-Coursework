/*
  Sujay Sundar
  rec07.cpp
  CS2124
  Recitation 07: Operator Overloading
  Implement the class Rational, so that the following program works.
 */

#include <iostream>
#include <ratio>
using namespace std;

int greatestCommonDivisor(int x, int y);

// Put your Rational class here.

class Rational {
    friend bool operator==(const Rational& leftRational, const Rational& rightRational);
    friend bool operator<(const Rational& leftRational, const Rational& rightRational);
    friend ostream& operator<<(ostream& os, const Rational& rational);
    friend istream& operator>>(istream& is, Rational& rational);
    friend Rational& operator--(Rational& rational);

public:
    Rational(int numerator = 0, int denominator = 1) : numerator(numerator), denominator(denominator) {norm();}
    void norm() {
        int GCD = greatestCommonDivisor(numerator, denominator);
        numerator /= GCD;
        denominator /= GCD;
        if (denominator < 0) {
            numerator = -numerator;
            denominator = -denominator;
        }
    }

    Rational& operator+=(const Rational& rational) {
        numerator = numerator * rational.denominator + rational.numerator * denominator;
        denominator *= rational.denominator;
        norm();
        return *this;
    }
    Rational& operator++() {
        numerator += denominator;
        return *this;
    }

    Rational operator++(int) {
        Rational state = *this;
        numerator += denominator;
        return state;
    }

    Rational operator--(int) {
        Rational state = *this;
        numerator -= denominator;
        norm();
        return state;
    }

    explicit operator bool() const {
        return numerator != 0;
    }


private:
    int numerator;
    int denominator;
};

ostream& operator<<(ostream& os, const Rational& rational) {
    os << rational.numerator << "/" << rational.denominator;
    return os;
}
istream& operator>>(istream& is, Rational& rational) {
    char slash;
    is >> rational.numerator >> slash >> rational.denominator;
    rational.norm();
    return is;
}

bool operator==(const Rational& leftRational, const Rational& rightRational) {
    return leftRational.numerator == rightRational.numerator && leftRational.denominator == rightRational.denominator;
}

bool operator<(const Rational& leftRational, const Rational& rightRational) {
    return leftRational.numerator * rightRational.denominator < leftRational.denominator * rightRational.numerator;
}

Rational& operator--(Rational& rational) {
    rational.numerator -= rational.denominator;
    rational.norm();
    return rational;
}

// Any functions that are not members and not friends should have
// prototypes here and their definitions after main.
Rational operator+(Rational leftRational, const Rational& rightRational);

Rational& operator--(Rational& rational);

bool operator!=(const Rational& leftRational, const Rational& rightRational);

bool operator<=(const Rational& leftRational, const Rational& rightRational);

bool operator>=(const Rational& leftRational, const Rational& rightRational);

bool operator>(const Rational& leftRational, const Rational& rightRational);

int main()
{
    Rational a, b;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "a: ";
    cin >> a;
    cout << "Input a rational number, e.g. 6/9.\n";
    cout << "b: ";
    cin >> b;
    const Rational one = 1;

    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    cout << "one = " << one << endl;
    cout << "a += b: " << (a += b) << endl;	// Implement as member
    cout << "a = " << a << endl;

    // Implement + as non-member, but not a friend
    cout << "a + one: " << (a + one) << endl;
    cout << "a == one: " << boolalpha << (a == one) << endl;

    // How does this manage to work?
    // It does NOT require writing another == operator.
    cout << "1 == one: " << boolalpha << (1 == one) << endl;

    // Do not implement as friend.
    cout << "a != one: " << boolalpha << (a != one) << endl;

    cout << "a = " << a << endl;
    cout << "++a = " << (++a) << endl;
    cout << "a = " << a << endl;
    cout << "a++ = " << (a++) << endl;
    cout << "a = " << a << endl;
    cout << "--a = " << (--a) << endl;
    cout << "a = " << a << endl;
    cout << "a-- = " << (a--) << endl;
    cout << "a = " << a << endl;

    cout << "++ ++a = " << (++ ++a) << endl;
    cout << "a = " << a << endl;
    cout << "-- --a = " << (-- --a) << endl;
    cout << "a = " << a << endl;

    cout << "a++ ++ = " << (a++ ++) << endl;
    cout << "a = " << a << endl;

    // Even though the above example, (a++ ++), compiled, the
    // following shouldn't.
    // But some compiler vendors might let it...  Is your compiler
    // doing the right thing? Why shouldn't it compile?
    //cout << "a-- -- = " << (a-- --) << endl;
    cout << "a = " << a << endl;


    // Should report that 1 is true
    if (Rational(1)) {
        cout << "1 is true" << endl;
    } else {
        cout << "1 is false" << endl;
    }

    // Should report that 0 is false
    if (Rational(0)) {
        cout << "0 is true" << endl;
    } else {
        cout << "0 is false" << endl;
    }

    cout << "Comparisons\n";
    Rational twoFifths(2, 5);
    Rational threeHalves(3, 2);
    Rational minusFive(-5);
    cout << twoFifths << " < " << threeHalves << " : "
         << (twoFifths < threeHalves) << endl;
    cout << twoFifths << " <= " << 1 << " : " << (twoFifths <= 1) << endl;
    cout << threeHalves << " < " << twoFifths << " : "
         << (threeHalves < twoFifths) << endl;
    cout << threeHalves << " > " << threeHalves << " : "
         << (threeHalves > threeHalves) << endl;
    cout << threeHalves << " >= " << threeHalves << " : "
         << (threeHalves >= threeHalves) << endl;
    cout << minusFive << " >= " << threeHalves << " : "
         << (minusFive >= threeHalves) << endl;
}

int greatestCommonDivisor(int x, int y)
{
    while (y != 0) {
        int temp = x % y;
        x = y;
        y = temp;
    }
    return x;
}

// Any functions that are not members and not friends should have
// their definitions here...

Rational operator+(Rational leftRational, const Rational& rightRational) {
    leftRational += rightRational;
    return leftRational;
}

bool operator!=(const Rational& leftRational, const Rational& rightRational) {
    return !(leftRational == rightRational);
}

bool operator<=(const Rational& leftRational, const Rational& rightRational) {
    return (leftRational < rightRational) || (leftRational == rightRational);
}

bool operator>=(const Rational& leftRational, const Rational& rightRational) {
    return !(leftRational < rightRational);
}

bool operator>(const Rational& leftRational, const Rational& rightRational) {
    return !(leftRational <= rightRational);
}

