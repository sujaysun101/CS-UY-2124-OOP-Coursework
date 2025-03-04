//Sujay Sundar

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

//Creates a Warrior struct that takes in a set of attributes: string name, int strength, and bool alive which has
//been set by default to true.
struct Warrior {
    string name;
    int strength;
    bool alive = true;
};

//Function prototype that create a new Warrior object by taking in a warrior name (passed by constant reference) and
//strength
Warrior createWarrior(const string& name, int strength);

//Function prototype that calculates the number of warriors based on the given file by taking in a vector of Warrior
//objects (passed by constant reference). Returns the size of vector as a default.
size_t calculateNumOfWarriors(const vector<Warrior>& listOfWarriors);

//Function prototype that displays the number of warriors based on the given file in a string format by taking in a
//vector of Warrior objects (passed by constant reference)
void displayNumOfWarriors(const vector<Warrior>& listOfWarriors);

//Function prototype that displays a list of all Warrior objects by their name and associated strength. Takes in a
//vector of Warrior objects (passed by constant reference).
void listAllWarriors(const vector<Warrior>& listOfWarriors);

//Function prototype that displays the number of Warriors and the information (name and strength) of each warrior as
//separate strings. Takes in a vector of Warrior objects (passed by constant reference).
void checkStatus(const vector<Warrior>& listOfWarriors);

//Function prototype that displays the names of two warrior names battling and the results of their battles. Takes in
//2 Warrior objects (both passed by reference).
void battleWarriors(Warrior& w1, Warrior& w2);

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
        if (first_word == "Warrior") {
            string name;
            int strength;

            //Reads in the name and strength from each line
            ifs >> name >> strength;

            //Uses the 'createWarrior' function to create a Warrior object and assign it to a new Warrior object 'w'.
            Warrior w = createWarrior(name, strength);

            //Adds object to vector of Warrior objects
            listOfWarriors.push_back(w);
        } else if (first_word == "Battle") {
            string name1;
            string name2;

            //Reads in the first and second names of two warriors from each line of the file.
            ifs >> name1 >> name2;

            //Uses the 'findWarriorIndex' function to return the index of a Warrior object based upon the name of the
            //warrior and reassigns that to the variables, index1 and index2, respectively.
            index1 = findWarriorIndex(listOfWarriors, name1);
            index2 = findWarriorIndex(listOfWarriors, name2);

            //Calls the 'battleWarriors' function with two Warrior objects, found using the indexes and vector of
            //Warrior objects.
            battleWarriors(listOfWarriors[index1], listOfWarriors[index2]);
        } else if (first_word == "Status") {
            //Calls the 'checkStatus' function to display the number of warriors and their respective information.
            checkStatus(listOfWarriors);
        }
    }

    return 0;
}

Warrior createWarrior(const string& name, int strength) {
    Warrior warrior;
    warrior.name = name;
    warrior.strength = strength;
    return warrior;
}


size_t calculateNumOfWarriors(const vector<Warrior>& listOfWarriors) {
    //Returns size of vector of Warrior objects.
    return listOfWarriors.size();
}

void displayNumOfWarriors(const vector<Warrior>& listOfWarriors) {
    //Assigns and initializes variable 'numOfWarriors' with the function call 'calculateNumOfWarriors'.
    int numOfWarriors = calculateNumOfWarriors(listOfWarriors);

    //Displays the number of warriors in appropriate format.
    cout << "There are: " << numOfWarriors << " warriors" << endl;
}

void listAllWarriors(const vector<Warrior>& listOfWarriors) {
    //For loop to loop through the vector of Warrior objects and display the name and strength of a Warrior for that
    //object, for all objects in the vector.
    for (size_t i = 0; i < listOfWarriors.size(); ++i) {
        cout << "Warrior: " << listOfWarriors[i].name << ", strength: " << listOfWarriors[i].strength << endl;
    }
}

void checkStatus(const vector<Warrior>& listOfWarriors) {
    //Calls two functions
        //One displays the number of warriors in the vector
        //The second displays a list of all the warrior names and strengths
    displayNumOfWarriors(listOfWarriors);
    listAllWarriors(listOfWarriors);
}

void battleWarriors(Warrior& w1, Warrior& w2) {
    //Displays the battle currently occurring between two warriors.
    cout << w1.name << " battles " << w2.name << endl;

    //Checks if both warriors are alive before battle occurs.
    if (w1.alive == true && w2.alive == true) {
        //Checks if the first warrior's strength is greater than the second warrior's.
        if (w1.strength > w2.strength) {
            //If so, displays that the first warrior defeated the second warrior
            cout << w1.name << " defeats " << w2.name << endl;

            //Redefines the first warrior's strength as the difference of its original strength minus it's opponent's
            //strength.
            w1.strength = w1.strength - w2.strength;

            //Sets the opponent's strength to 0
            w2.strength = 0;

            //Sets the opponent's alive status to false.
            w2.alive = false;
        //Logic for this else-if is the same, but vice-versa. (e.g. checks if the second warrior's strength is greater
        //than the first, etc.)
        } else if (w1.strength < w2.strength) {
            cout << w2.name << " defeats " << w1.name << endl;
            w2.strength = w2.strength - w1.strength;
            w1.strength = 0;
            w1.alive = false;
        //Checks If both warriors are dead
        } else {
            //If so, displays that both are dead
            cout << "Mutual Annihilation: " << w1.name << " and " << w2.name << " die at each other's hands" << endl;

            //Sets both warrior's alive status and strengths to false and 0, respectively.
            w1.alive = false;
            w1.strength = 0;
            w2.alive = false;
            w2.strength = 0;
        }
    //Checks if the first warrior has already been killed in a previous battle.
    } else if (w1.alive == false && w2.alive == true) {
        //If so, displays an error message and sets his strength to 0.
        cout << "He's dead, " << w2.name << endl;
        w1.strength = 0;
    //Checks if the second warrior has already been killed in a previous battle.
    } else if (w1.alive == true && w2.alive == false) {
        //If so, displays an error message and sets his strength to 0.
        cout << "He's dead, " << w1.name << endl;
        w2.strength = 0;
    //Checks if both warriors have already been killed in a previous battle.
    } else if (w1.alive == false && w2.alive == false) {
        //Displays an error message.
        cout << "Oh, NO! They're both dead! Yuck!" << endl;
    }
}

size_t findWarriorIndex(const vector<Warrior>& listOfWarriors, const string& name) {
    //For loop to loop through the vector of Warrior objects.
    for (size_t i = 0; i < listOfWarriors.size(); ++i) {
        //If the Warrior object's name attribute, at each index is the same as the name argument passed in, return the
        //index of that Warrior object.
        if (listOfWarriors[i].name == name) {
            return i;
        }
    }
    //Returns the vector's size as a default value. Function has to have a return type, or else 'return i' won't work.
    return listOfWarriors.size();
}

