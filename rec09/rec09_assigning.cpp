//Sujay Sundar
//rec09
//Inheritance tutorial

#include <iostream>
using namespace std;

class Base {
public:
    Base() {}
};

class Derived : public Base {
public:
    Derived() {}
};

int main() {
    Base base;
    Derived derived;
    Base* basePtr = nullptr;
    Derived* derivedPtr = nullptr;

    Base boseCopy = derived;
    //Derived derivedCopy = base;

    basePtr = derivedPtr;
    //derivedPtr = basePtr;

    basePtr = &base;
    basePtr = &derived;
    derivedPtr = &derived;
    //derivedPtr = &base;
}