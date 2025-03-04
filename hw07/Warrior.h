#ifndef WARRIOR_H
#define WARRIOR_H

#include <iostream>
#include <string>

#include "Noble.h"

namespace WarriorCraft {
    class Noble;
    //Created Warrior class
    class Warrior {
        //friend output operator prototype
        friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);
    public:
        //Warrior constructor with initialization list. jobStatus set to default
        //false
        Warrior(const std::string& name, double strength);
        //Getters to return warrior name, strength, and job status
        const std::string& getWarriorName() const;
        double getWarriorStrength() const;
        //Setters to set the warrior's job status and strength
        void setNoble(Noble* theNoble);
        void setWarriorStrength(double theStrength);
        void runaway();
        bool isHired();
    private:
        //Private member variables of name (string), strength (double), and
        //jobStatus (bool)
        std::string name;
        double strength;
        Noble* noble;
    };
}

#endif //WARRIOR_H
