#include "Noble.h"
#include "Warrior.h"

using namespace std;

namespace WarriorCraft {
	//Function prototype to find the index of the noble pointer within the vector of Noble pointers.
	//Takes in this vector (passed by constant reference) and the name of the noble (passed by constant reference)
	size_t findNobleIndex(const vector<Noble*>& nobles, const string& nobleName);

	//Function prototype to find the index of the warrior pointer within the vector of Warrior pointers.
	//Takes in this vector (passed by constant reference) and the name of the warrior (passed by constant reference)
	size_t findWarriorIndex(const vector<Warrior*>& warriors, const string& warriorName);

    //Created a Noble class
Noble::Noble(const string& nobleName) : nobleName(nobleName), status(true) {}
	const string& Noble::getNobleName() const {return nobleName;}
	//hire method that returns a bool and takes in a warrior object (passed
	//by reference)
    bool Noble::hire(Warrior& warrior) {
		//Check if warrior's job status is true and whether noble is dead
		if (warrior.isHired() == true || status == false) {
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
			warrior.setNoble(this);
			return true;
		}
    }
	//Method that finds the Warrior's index and returns it. Takes in a
	//warrior object (passed by reference)
	size_t Noble::findWarriorIndex(const Warrior& warrior) const {
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
	bool Noble::fire(Warrior& warrior) {
		//If the warrior's job status is false and the noble's is dead
		if (warrior.isHired() == false || status == false) {
			//Display the "noble's name failed to fire the warrior's name"
			cout << nobleName << " failed to fire " <<
				warrior.getWarriorName() << endl;
			return false;
			//If the above condition is false, check whether the warrior's
			//job status is true
		} else if (warrior.isHired() == true) {
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
				warrior.setNoble(nullptr);

				removeWarrior(warrior);

				//Display the "warrior's name, you don't work for me any
				//more! -- noble's name"
				cout << warrior.getWarriorName() <<
					", you don't work for me any more! -- " << nobleName <<
						endl;
				return true;
			}
		}
	}
	void Noble::removeWarrior(Warrior& warrior) {
		size_t index = findWarriorIndex(warrior);
		//Uses a bubble sort to shift all the elements into their proper position and pops the element at the index
		//we want to remove.
		for (size_t i = index; i < army.size() - 1; ++i) {
			army[i] = army[i + 1];
		}
		army.pop_back();
	}

	//armyStrength method that returns the totalStrength (double) of the
	//army, by summing up each warrior's strengths.
	double Noble::armyStrength() const {
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
	void Noble::winnerStrengthAfterBattle(double ratio) {
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
	void Noble::loserStrengthAfterBattle() {
		for (size_t i = 0; i < army.size(); ++i) {
			army[i]->setWarriorStrength(0);
		}
	}
	//battle method that takes in a noble object (passed by reference)
	void Noble::battle(Noble& noble) {
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

	//findNobleIndex function definition
	size_t findNobleIndex(const vector<Noble*>& nobles, const string& nobleName) {
	for (size_t i = 0; i < nobles.size(); ++i) {
		//If the noble pointer's name at that index is equal to the noble's name in the file, return the index
		if (nobles[i]->getNobleName() == nobleName) {
			return i;
		}
	}
	//Or else, return the size of the vector of Noble pointers
	return nobles.size();
}

	//findWarriorIndex function definition
	size_t findWarriorIndex(const vector<Warrior*>& warriors, const string& warriorName) {
	for (size_t i = 0; i < warriors.size(); ++i) {
		//If the warrior pointer's name at that index is equal to the warrior's name in the file, return the index
		if (warriors[i]->getWarriorName() == warriorName) {
			return i;
		}
	}
	//Or else, return the size of the vector of Warrior pointers
	return warriors.size();
}

}

