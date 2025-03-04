/*
Sujay Sundar
hw06.cpp
Operator Overloading
*/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Put your class and all function definitions here.
//Created the BigUnsigned class
class BigUnsigned {
     //friend operators
     friend bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs);
     friend bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs);
     friend ostream& operator<<(ostream& os, const BigUnsigned& big_unsigned);
     friend BigUnsigned& operator--(BigUnsigned& big_unsigned);
public:
     //First constructor will take in a digit (int) set to default 0 and will add a digit to the vector of ints 'digits' when called
     BigUnsigned(int digit = 0) {digits.push_back(digit);}
     //Second constructor takes in a strOfDigits (string - passed by constant reference)
     BigUnsigned(const string& strOfDigits) {
          int index = 0;
          //While the index is less than the size of strOfDigits and the beginning character of this string is '0', increment the index.
          while (index < strOfDigits.size() && strOfDigits[index] == '0') {
               ++index;
          }

          for (int i = strOfDigits.size() - 1; i >= index; --i) {
               //If the current character in strOfDigits is between 0 and 9 (inclusive), add that character (convert to an int) to the vector of ints 'digits'
               if (strOfDigits[i] >= '0' && strOfDigits[i] <= '9') {
                    digits.push_back(strOfDigits[i] - '0');
               }
          }
          //If the vector of ints 'digits' is empty, add '0' to the vector
          if (digits.empty()) {
               digits.push_back(0);
          }
     }
     //Output operator that takes in an ostream variable (passed by reference) and a BigUnsigned object (passed by constant reference)
     friend ostream& operator<<(ostream& os, const BigUnsigned& big_unsigned) {
          //Iterate through the digits in reverse order
          for (int i = big_unsigned.digits.size() - 1; i >= 0; --i) {
               //Output each digit in this order
               os << big_unsigned.digits[i];
          }
          return os;
     }
     //Addition operator that takes in 2 BigUnsigned objects (passed by constant reference), one that represents the term to the left of the operator and the other representing the term to the right of the operator
     friend BigUnsigned operator+(const BigUnsigned& lhs, const BigUnsigned& rhs) {
          BigUnsigned state;
          //Clear anything previously stored in the object's vector
          state.digits.clear();
          int carryDigit = 0;
          size_t max_size;
          //If the digits on the left-hand side is the greater than the digits on the right-hand side, set the max_size to the digits on the left-hand side
          if (lhs.digits.size() > rhs.digits.size()) {
               max_size = lhs.digits.size();
          //If the digits on the right-hand side is the greater than or equal to the digits on the left-hand side, set the max_size to the digits on the right-hand side
          } else {
               max_size = rhs.digits.size();
          }
          for (size_t i = 0; i < max_size; ++i) {
               int lhsDigit = 0;
               int rhsDigit = 0;
               //If the index is less than the size of the digits vector on the left-hand side, assign the lhsDigit to the current index's left-hand side digit
               if (i < lhs.digits.size()) {
                    lhsDigit = lhs.digits[i];
               }
               //If the index is less than the size of the digits vector on the right-hand side, assign the rhsDigit to the current index's right-hand side digit
               if (i < rhs.digits.size()) {
                    rhsDigit = rhs.digits[i];
               }
               //sum is the sum of the lhsDigit, rhsDigit, and carryDigit
               int sum = lhsDigit + rhsDigit + carryDigit;
               //modDigit is the modulus of the sum by 10
               int modDigit = sum % 10;
               //define carryDigit as the sum divided by 10
               carryDigit = sum / 10;
               //Add the modulus to the vector
               state.digits.push_back(modDigit);
          }
          //if the carryDigit is greater than 0, add it to the vector
          if (carryDigit > 0) {
               state.digits.push_back(carryDigit);
          }
          return state;
     }
     //Plus-equals operator that adds a BigUnsigned object (passed by constant reference) to the current object and assigns the sum to the curren object
     BigUnsigned& operator+=(const BigUnsigned& big_unsigned) {
          *this = *this + big_unsigned;
          return *this;
     }
     //Pre-increment operator that increments the current BigUnsigned object by one and returns a reference to this object
     BigUnsigned& operator++() {
          *this += 1;
          return *this;
     }
     //Post-increment operator that increments the current BigUnsigned object by one. Returns that current object, instead of the increment one
     BigUnsigned operator++(int) {
          BigUnsigned state = *this;
          ++(*this);
          return state;
     }
     //Explicit bool conversion operator to check whether the BigUnsigned object is not zero.
     explicit operator bool() const {
          return !(*this == BigUnsigned(0));
     }
     //Equality operator (friend) that checks whether the lhs and rhs (passed by constant reference) have their digits in the same order
     friend bool operator==(const BigUnsigned& lhs, const BigUnsigned& rhs) {
          return lhs.digits == rhs.digits;
     }
     //Not-equals operator that checks whether the lhs and rhs objects are not indentical
     friend bool operator!=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
          return !(lhs == rhs);
     }
     //Less than operator (friend) that compares the lhs and rhs (passed by constant reference).
     friend bool operator<(const BigUnsigned& lhs, const BigUnsigned& rhs) {
          //If the size of the digits vectors on the left and right are not equal to each other, return the smaller size
          if (lhs.digits.size() != rhs.digits.size()) {
               return lhs.digits.size() < rhs.digits.size();
          }
          for (int i = lhs.digits.size() - 1; i >= 0; --i) {
               if (lhs.digits[i] != rhs.digits[i]) {
                    return lhs.digits[i] < rhs.digits[i];
               }
          }
          return false;
     }
     //Greater-than operator that compares the rhs and lhs. Returns true if the lhs is greater than the rhs. Returns false otherwise.
     friend bool operator>(const BigUnsigned& lhs, const BigUnsigned& rhs) {
          return rhs < lhs;
     }
     //Less-than-or-equal operator that returns true if the lhs is less than or equal to the rhs
     friend bool operator<=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
          return !(lhs > rhs);
     }
     //Greater-than-or-equal operator that returns true if the lhs is greater than or equal to the rhs
     friend bool operator>=(const BigUnsigned& lhs, const BigUnsigned& rhs) {
          return !(lhs < rhs);
     }
private:
    vector<int> digits;
};

int main()
{
    BigUnsigned zero;
    BigUnsigned one(1);

    cout << "zero: " << zero << endl;
    cout << "one: " << one << endl;

    BigUnsigned val = 1;
    cout << "val: " << val << endl;
    cout << "++val: " << ++val << endl;
    cout << "val: " << val << endl;
    cout << "val++: " << val++ << endl;
    cout << "val: " << val << endl;

    cout << "(one + zero): " << (one + zero) << endl;
    cout << "(one + one): " <<  (one + one) << endl;

    cout << boolalpha;
    cout << "one < one: " << (one < one) << endl;
    cout << "zero < one: " << (zero < one) << endl;

    BigUnsigned a = 123;
    BigUnsigned b = 1234;
    BigUnsigned c = 124;
    BigUnsigned d = 12345;

    cout << "a: " << a << ", b: " << b
         << ", c: " << c << ", d: " << d << endl;
    cout << "a + d: " << (a + d) << endl;
    cout << "d + d: " << (d + d) << endl;
    cout << "a < d: " << (a < d) << endl;
    cout << "d < a: " << (d < a) << endl;
    cout << "zero == zero: " << (zero == zero) << endl
         << "zero == one: " << (zero == one) << endl
         << "a == a: " << (a == a) << endl
         << "a == d: " << (a == d) << endl
         << "d == a: " << (d == a) << endl;

    cout << "(zero == 0): " << (zero == 0) << endl
         << "(one == 0): " << (one == 0) << endl
         << "(1 == one): " << (1 == one) << endl;

    // +=
    cout << "b: " << b << ", c: " << c << endl;
    cout << "(c += b): " << (c += b) << endl;
    cout << "b: " << b << ", c: " << c << endl;


    BigUnsigned x = a;
    cout << "x: " << x << ", a: " << a << endl
         << "x == a: " << (x == a) << endl
         << "a == x: " << (a == x) << endl
         << "a < x: " << (a < x) << endl
         << "a > x: " << (a > x) << endl;

    cout << "x > a: " << (x > a) << endl
         << "x >= a: " << (x >= a) << endl
         << "x <= a: " << (x <= a) << endl
         << "x != a: " << (x != a) << endl;


    BigUnsigned big("987654321");
    BigUnsigned big2("  ");
    BigUnsigned big3("felix");
    BigUnsigned big4("00987654321");

    cout << "big: " << big << endl
         << "big2: " << big2 << endl
         << "big3: " << big3 << endl
         << "big4: " << big4 << endl;

    BigUnsigned big5(98765);
    BigUnsigned big6(2457);
    cout << "big5: " << big5  << ", big6: " <<  big6 << endl
         << "(big5 + big6): " << (big5 + big6) << endl
         << "(big6 + big5): " << (big6 + big5) << endl;


    // How does this work?
    cout << zero << " is " << (zero ? "true" : "false") << endl;
    cout << one << " is " << (one ? "true" : "false") << endl;
    cout << big4 << " is " << (big4 ? "true" : "false") << endl;
} // main

