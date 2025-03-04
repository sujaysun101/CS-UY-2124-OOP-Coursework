/*
  Sujay Sundar
  hw04.cpp
  hw04: Classes, pointers and association
 */

#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Your Noble and Warrior classes should go here.
// ...

//Created Warrior class
class Warrior {
	//friend output operator prototype
	friend ostream& operator<<(ostream& os, const Warrior& warrior);
public:
	//Warrior constructor with initialization list. jobStatus set to default
	//false
     Warrior(const string& name, double strength) : name(name),
	strength(strength), jobStatus(false) {}
	//Getters to return warrior name, strength, and job status
     const string& getWarriorName() const {return name;}
     double getWarriorStrength() const {return strength;}
     bool getWarriorJobStatus() const {return jobStatus;}
	//Setters to set the warrior's job status and strength
     void setWarriorJobStatus(bool theStatus) {jobStatus = theStatus;}
	void setWarriorStrength(double theStrength) {strength = theStrength;}
private:
	//Private member variables of name (string), strength (double), and
	//jobStatus (bool)
  string name;
  double strength;
  bool jobStatus;
};

//Output operator that displays the warrior's name: warrior's strength
ostream& operator<<(ostream& os, const Warrior& warrior) {
	os << "\t" << warrior.name << ": " << warrior.strength;
	os << endl;
	return os;
}

//Created a Noble class
class Noble {
	//friend output operator prototype
  	friend ostream& operator<<(ostream& os, const Noble& noble);
public:
	//Noble constructor with initialization list. status (whether noble is
	//alive or dead) set to default true
	Noble(const string& nobleName) : nobleName(nobleName), status(true) {}
	//hire method that returns a bool and takes in a warrior object (passed
	//by reference)
    bool hire(Warrior& warrior) {
		//Check if warrior's job status is true and whether noble is dead
		if (warrior.getWarriorJobStatus() == true || status == false) {
			//Display the "noble's name failed to hire warrior's name"
			cout << nobleName << " failed to hire " <<
				warrior.getWarriorName() << endl;
			return false;
		} else {
			//Otherwise:
			//Add the address of the warrior object into the vector of
			//Warrior pointers (army)
			army.push_back(&warrior);
			//Set the warrior's job status to true
			warrior.setWarriorJobStatus(true);
			return true;
		}
    }
	//Method that finds the Warrior's index and returns it. Takes in a
	//warrior object (passed by reference)
	size_t findWarriorIndex(const Warrior& warrior) const {
		for (size_t i = 0; i < army.size(); ++i) {
			//If the warrior pointer at that index, i is equal to the
			//address of the warrior object, return the index
			if (army[i] == &warrior) {
				return i;
			}
		}
		//Or, return the size of the vector
		return army.size();
	}
	//fire method that takes in a warrior object (passed by reference)
	bool fire(Warrior& warrior) {
		//If the warrior's job status is false and the noble's is dead
		if (warrior.getWarriorJobStatus() == false || status == false) {
			//Display the "noble's name failed to fire the warrior's name"
			cout << nobleName << " failed to fire " <<
				warrior.getWarriorName() << endl;
			return false;
			//If the above condition is false, check whether the warrior's
			//job status is true
		} else if (warrior.getWarriorJobStatus() == true) {
			//Assign a new index variable the method call
			//findWarriorIndex(warrior), which returns i.
			size_t index = findWarriorIndex(warrior);
			//If the index is equal to the vector's size
			if (index == army.size()) {
				//Display the "noble's name failed to fire the warrior's name"
				cout << nobleName << " failed to fire " <<
					warrior.getWarriorName() << endl;
				return false;
				//Otherwise:
			} else {
				//Set the warrior's job status to false
				warrior.setWarriorJobStatus(false);

				//Use a bubble sort to move that index's warrior pointer to
				//the back of the vector.
				for (size_t i = index; i < army.size() - 1; ++i) {
					army[i] = army[i + 1];
				}
				//Then use the "pop_back" method to remove (fire) the warrior.
				army.pop_back();
				//Display the "warrior's name, you don't work for me any
				//more! -- noble's name"
				cout << warrior.getWarriorName() <<
					", you don't work for me any more! -- " << nobleName <<
						endl;
				return true;
			}
		}
	}
	//armyStrength method that returns the totalStrength (double) of the
	//army, by summing up each warrior's strengths.
	double armyStrength() const {
		//Initializes the totalStrength double to 0.0
		double totalStrength = 0.0;
		//For loop that adds each warrior's strength to the totalStrength
		for (size_t i = 0; i < army.size(); ++i) {
			totalStrength += army[i]->getWarriorStrength();
		}
		return totalStrength;
	}
	//Decreases the winner's strength after a battle occurs. Takes in a ratio
	//(double).
	void winnerStrengthAfterBattle(double ratio) {
		for (size_t i = 0; i < army.size(); ++i) {
			double difference;
			//Initializes difference (double) to each warrior pointer
			//at the index, i multiplied by the ratio.
			difference = army[i]->getWarriorStrength() * ratio;
			//Set the warrior's strength to the current strength
			//subtracted by the difference.
			army[i]->setWarriorStrength(army[i]->getWarriorStrength()
				- difference);
		}
	}
	//Sets the loser's strength to zero
	void loserStrengthAfterBattle() {
		for (size_t i = 0; i < army.size(); ++i) {
			army[i]->setWarriorStrength(0);
		}
	}
	//battle method that takes in a noble object (passed by reference)
	void battle(Noble& noble) {
        //Displays the battle currently occurring between two warriors.
        cout << nobleName << " battles " << noble.nobleName << endl;

        //Checks if both nobles are alive before battle occurs.
        if (noble.status == true && status == true) {

            //Checks if the first noble's army strength is greater than the
            //second noble's.
            if (armyStrength() > noble.armyStrength()) {
                //If so, displays that the first noble defeated the second
                //noble
                cout << nobleName << " defeats " << noble.nobleName << endl;

                //Defines a ratio (double), which is the second noble's army
                //strength divided by the first noble's
            	double ratio = noble.armyStrength()/armyStrength();
            	//Calls the winnerStrengthAfterBattle method, passing in ratio.
                winnerStrengthAfterBattle(ratio);

                //Sets the second noble's strength to 0.
                noble.loserStrengthAfterBattle();

            	//Sets the second noble's status to false (dead)
            	noble.status = false;

            //Logic for this else-if is the same, but vice-versa.
            //(e.g. checks if the second noble's army strength is
            //greater than the first, etc.)
            } else if (armyStrength() < noble.armyStrength()) {
                cout << noble.nobleName << " defeats " << nobleName << endl;
            	double ratio = armyStrength()/noble.armyStrength();
            	noble.winnerStrengthAfterBattle(ratio);

                loserStrengthAfterBattle();

            	status = false;

            //Checks If both nobles are dead
            } else {
                //If so, displays that both are dead
                cout << "Mutual Annihilation: " << nobleName << " and " <<
                	noble.nobleName << " die at each other's hands" <<
                    endl;

                //Sets each warrior's strength to 0, respectively.
                loserStrengthAfterBattle();
                noble.loserStrengthAfterBattle();

            	//Sets their statuses to false (dead)
            	status = false;
            	noble.status = false;
            }

        //Checks if the first noble has already been killed in a previous
        //battle.
        } else if (status == false && noble.status == true) {
            //If so, displays an error message.
            cout << "He's dead, " << noble.nobleName << endl;
        //Checks if the second noble has already been killed in a previous
        //battle.
        } else if (status == true && noble.status == false) {
            //If so, displays an error message.
            cout << "He's dead, " << nobleName << endl;
        //Checks if both nobles have already been killed in a previous
        //battle.
        } else if (status == false && noble.status == false) {
            //Displays an error message.
            cout << "Oh, NO! They're both dead! Yuck!" << endl;
        }
    }
private:
	//Private member variable of noble's name (string), life status (bool),
	//and army (vector of Warrior pointers)
  string nobleName;
  bool status;
  vector<Warrior*> army;
};

//Output operator that displays the "second noble's name has an army of the
//noble's army size"
ostream& operator<<(ostream& os, const Noble& noble) {
	os << noble.nobleName << " has an army of " << noble.army.size() << endl;
	//Loops through army vector and displays the dereference of each pointer
	//in the vector.
	for (size_t i = 0; i < noble.army.size(); ++i) {
		os << *noble.army[i];
	}
     return os;
}

int main()
{

    Noble art("King Arthur");
    Noble lance("Lancelot du Lac");
    Noble jim("Jim");
    Noble linus("Linus Torvalds");
    Noble billie("Bill Gates");

    Warrior cheetah("Tarzan", 10);
    Warrior wizard("Merlin", 15);
    Warrior theGovernator("Conan", 12);
    Warrior nimoy("Spock", 15);
    Warrior lawless("Xena", 20);
    Warrior mrGreen("Hulk", 8);
    Warrior dylan("Hercules", 3);

    jim.hire(nimoy);
    lance.hire(theGovernator);
    art.hire(wizard);
    lance.hire(dylan);
    linus.hire(lawless);
    billie.hire(mrGreen);
    art.hire(cheetah);
    art.hire(nimoy);

    cout << "==========\n\n"
         << "Status before all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n\n";

    art.fire(cheetah);
    cout << art << endl;

    lance.fire(nimoy);
    cout << lance << endl;
    cout << "==========\n\n";

    art.battle(lance);
    jim.battle(lance);
    linus.battle(billie);
    billie.battle(lance);

    cout << "==========\n\n"
         << "Status after all battles, etc.\n";
    cout << jim << endl;
    cout << lance << endl;
    cout << art << endl;
    cout << linus << endl;
    cout << billie << endl;
    cout << "==========\n";

} // main
