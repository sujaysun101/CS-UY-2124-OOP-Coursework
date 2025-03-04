#include "Warrior.h"
#include "Noble.h"

using namespace std;

namespace WarriorCraft {
    //Created Warrior class
    Warrior::Warrior(const string& name, double strength) : name(name),
        strength(strength), noble(nullptr) {}
    //Getters to return warrior name, strength, and job status
    const string& Warrior::getWarriorName() const {return name;}
    double Warrior::getWarriorStrength() const {return strength;}
    //Setters to set the warrior's job status and strength
    void Warrior::setNoble(Noble* theNoble) {noble = theNoble;}
    void Warrior::setWarriorStrength(double theStrength) {strength = theStrength;}
    void Warrior::runaway() {
        //Calls the removeWarrior method from the Noble class on itself
        noble->removeWarrior(*this);
        //Displays the warrior's name fleeing from his noble (name)
        cout << name << " flees in terror, abandoning his lord, " << noble->getNobleName();
        //Sets noble pointer to nullptr
        noble = nullptr;
    }
    bool Warrior::isHired() {
        //If there is no pointer to the noble object, return false
        if (noble == nullptr) {
            return false;
        //Else, return true
        } else {
            return true;
        }
    }

    //Output operator that displays the warrior's name: warrior's strength
    ostream& operator<<(ostream& os, const Warrior& warrior) {
        os << "\t" << warrior.name << ": " << warrior.strength;
        os << endl;
        return os;
    }
}
