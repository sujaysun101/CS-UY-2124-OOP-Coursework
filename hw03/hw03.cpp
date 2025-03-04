//Sujay Sundar
//hw03.cpp
//Data hiding, encapsulation, delegation, overloading the output operator
//Net ID: sss9869

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Created a Warrior Class
class Warrior {
public:
    //Nested a public Weapon class within the Warrior class
    class Weapon {
        //Friend prototype of Weapon output operator
        friend ostream& operator<<(ostream& os, const Weapon& w);
    public:
        //Constructor to Weapon class. Initializes weaponName and weaponStrength
        Weapon(const string& weaponName, int weaponStrength) : weaponName(weaponName), weaponStrength(weaponStrength)
        {}

        //getWeaponName returns the weaponName
        const string& getWeaponName() const {return weaponName;}

        //getWeaponStrength returns the weaponStrength
        int getWeaponStrength() const {return weaponStrength;}

        //setWeaponStrength sets the weaponStrength
        void setWeaponStrength(int theStrength) {weaponStrength = theStrength;}

    //Creates private member variables of weaponName (string) and weaponStrength (int)
    private:
        string weaponName;
        int weaponStrength;
    };

    //Constructor to Warrior class. Initializes name and then initializes weaponName and weaponStrength to weapon
    //object.
    Warrior(const string& name, const string& weaponName, int weaponStr) : name(name), weapon(weaponName, weaponStr)
    {};

    //getWarriorName returns the warrior's name.
    const string& getWarriorName() const {return name;}

    //battleWarriors method that takes in a Warrior object (passed-by reference)
    void battleWarriors(Warrior& warrior) {
        //Displays the battle currently occurring between two warriors.
        cout << name << " battles " << warrior.name << endl;

        //Checks if both warriors are alive before battle occurs.
        if (weapon.getWeaponStrength() != 0 && warrior.weapon.getWeaponStrength() != 0) {

            //Checks if the first warrior's strength is greater than the second warrior's.
            if (weapon.getWeaponStrength() > warrior.weapon.getWeaponStrength()) {
                //If so, displays that the first warrior defeated the second warrior
                cout << name << " defeats " << warrior.name << endl;

                //Redefines the first warrior's strength as the difference of its original strength minus it's
                //opponent's strength.
                weapon.setWeaponStrength(weapon.getWeaponStrength() - warrior.weapon.getWeaponStrength());

                //Sets the opponent's strength to 0
                warrior.weapon.setWeaponStrength(0);

            //Logic for this else-if is the same, but vice-versa. (e.g. checks if the second warrior's strength is
            //greater than the first, etc.)
            } else if (weapon.getWeaponStrength() < warrior.weapon.getWeaponStrength()) {
                cout << name << " defeats " << warrior.name << endl;
                warrior.weapon.setWeaponStrength(warrior.weapon.getWeaponStrength() - weapon.getWeaponStrength());
                weapon.setWeaponStrength(0);

            //Checks If both warriors are dead
            } else {
                //If so, displays that both are dead
                cout << "Mutual Annihilation: " << name << " and " << warrior.name << " die at each other's hands" <<
                    endl;

                //Sets each warrior's strength to 0, respectively.
                weapon.setWeaponStrength(0);
                warrior.weapon.setWeaponStrength(0);
            }

        //Checks if the first warrior has already been killed in a previous battle.
        } else if (weapon.getWeaponStrength() == 0 && warrior.weapon.getWeaponStrength() != 0) {
            //If so, displays an error message and sets his strength to 0.
            cout << "He's dead, " << warrior.name << endl;
            weapon.setWeaponStrength(0);

        //Checks if the second warrior has already been killed in a previous battle.
        } else if (weapon.getWeaponStrength() != 0 && warrior.weapon.getWeaponStrength() == 0) {
            //If so, displays an error message and sets his strength to 0.
            cout << "He's dead, " << name << endl;
            warrior.weapon.setWeaponStrength(0);

        //Checks if both warriors have already been killed in a previous battle.
        } else if (weapon.getWeaponStrength() == 0 && warrior.weapon.getWeaponStrength() == 0) {
            //Displays an error message.
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
    }

    //Friend prototypes for both Warrior (parent) class and Weapon (child/nested) class
    friend ostream& operator<<(ostream& os, const Warrior& wa);
    friend ostream& operator<<(ostream& os, const Weapon& w);

//Creates private member variables of (warrior's) name (string) and weapon (Weapon object)
private:
    string name;
    Weapon weapon;
};



//Function prototype that displays the number of Warriors and the information (warrior name, weapon name, and weapon
//strength). Takes in a vector of Warrior objects (passed by constant reference).
void checkStatus(const vector<Warrior>& listOfWarriors);

//Function prototype that finds and returns the index of the Warrior object in a vector. Takes in a vector of Warrior
//objects (passed by constant reference) and a string name (passed by constant reference)
size_t findWarriorIndex(const vector<Warrior>& listOfWarriors, const string& name);

int main()
{
    //Opens file 'warriors.txt'
    ifstream ifs("warriors.txt");

    //If file doesnt open, displays error message and exits out of program.
    if (!ifs) {
        cerr << "failed to open warriors.txt";
        exit(1);
    }

    //Creates an uninitialized string type 'first_word'. Represents the first word of each line of the file.
    string first_word;

    //Creates an empty vector of Warrior objects.
    vector<Warrior> listOfWarriors;

    //Represents two index variables. One for finding the first Warrior object in the vector and the other for finding
    //the second object.
    size_t index1;
    size_t index2;

    //While loop to read the first word of each line
    while (ifs >> first_word) {
        //Checks if first word is Warrior command.
        if (first_word == "Warrior") {
            string warriorName;
            string weaponName;
            int weaponStrength;

            //Reads in the warriorName, weaponName, and weaponStrength from each line
            ifs >> warriorName >> weaponName >> weaponStrength;

            //Initializes warrior object with warriorName, weaponName, and weaponStrength.
            Warrior warrior(warriorName, weaponName, weaponStrength);

            //Adds warrior to vector of Warrior objects, listOfWarriors.
            listOfWarriors.push_back(warrior);
        //Checks if first word is Battle command.
        } else if (first_word == "Battle") {
            string name1;
            string name2;

            //Reads in the first and second names of two warriors from each line of the file.
            ifs >> name1 >> name2;

            //Uses the 'findWarriorIndex' function to return the index of a Warrior object based upon the name of the
            //warrior and reassigns that to the variables, index1 and index2, respectively.
            index1 = findWarriorIndex(listOfWarriors, name1);
            index2 = findWarriorIndex(listOfWarriors, name2);

            //Calls the 'battleWarriors' method in the Warrior class, with two Warrior objects, found using the indexes
            //to search through the vector of Warrior objects.
            listOfWarriors[index1].battleWarriors(listOfWarriors[index2]);
        //Checks if first word is Status command.
        } else if (first_word == "Status") {
            //Calls the 'checkStatus' function to display the number of warriors and their respective information.
            checkStatus(listOfWarriors);
        }
    }

    return 0;
}

//Output Operator to display the weapon's name and strength
ostream& operator<<(ostream& os, const Warrior::Weapon& weapon) {
    os << weapon.weaponName << ", " << weapon.weaponStrength;
    return os;
}

//Output Operator to display the warrior's name and its weapon's characteristics
//Calls from the previous output operator to display the weapon's name and strength.
ostream& operator<<(ostream& os, const Warrior& wa) {
    os << "Warrior: " << wa.name << ", weapon: " << wa.weapon;
    return os;
}

void checkStatus(const vector<Warrior>& listOfWarriors) {
    //Initializes numOfWarriors (int) variable to vector of Warrior objects' size.
    int numOfWarriors = listOfWarriors.size();

    //Displays how many warriors there are
    cout << "There are: " << numOfWarriors << " warriors" << endl;

    //Calls output operator to display each Warrior object
    for (size_t i = 0; i < listOfWarriors.size(); ++i) {
        cout << listOfWarriors[i] << endl;
    }
}

size_t findWarriorIndex(const vector<Warrior>& listOfWarriors, const string& name) {
    //For loop to loop through the vector of Warrior objects.
    for (size_t i = 0; i < listOfWarriors.size(); ++i) {
        //If the Warrior object's name attribute, at each index is the same as the name argument passed in, return the
        //index of that Warrior object.
        if (listOfWarriors[i].getWarriorName() == name) {
            return i;
        }
    }

    //Returns the vector's size as a default value. Function has to have a return type, or else 'return i' won't work.
    return listOfWarriors.size();
}

