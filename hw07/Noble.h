#ifndef NOBLE_H
#define NOBLE_H

#include <iostream>
#include <vector>
#include <string>
#include "Warrior.h"

namespace WarriorCraft {
    class Warrior;
    //Created a Noble class
    class Noble {
        //friend output operator prototype
        friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
    public:
        //Noble constructor with initialization list. status (whether noble is
        //alive or dead) set to default true
        Noble(const std::string& nobleName);
        const std::string& getNobleName() const;
        //hire method that returns a bool and takes in a warrior object (passed
        //by reference)
        bool hire(Warrior& warrior);
        //Method that finds the Warrior's index and returns it. Takes in a
        //warrior object (passed by reference)
        size_t findWarriorIndex(const Warrior& warrior) const;
        //fire method that takes in a warrior object (passed by reference)
        bool fire(Warrior& warrior);
        void removeWarrior(Warrior& warrior);
        //armyStrength method that returns the totalStrength (double) of the
        //army, by summing up each warrior's strengths.
        double armyStrength() const;
        //Decreases the winner's strength after a battle occurs. Takes in a ratio
        //(double).
        void winnerStrengthAfterBattle(double ratio);
        //Sets the loser's strength to zero
        void loserStrengthAfterBattle();
        //battle method that takes in a noble object (passed by reference)
        void battle(Noble& noble);
    private:
        //Private member variable of noble's name (string), life status (bool),
        //and army (vector of Warrior pointers)
        std::string nobleName;
        bool status;
        std::vector<Warrior*> army;
    };
}
#endif
