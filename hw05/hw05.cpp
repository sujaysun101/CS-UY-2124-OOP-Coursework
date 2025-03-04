/*
 Sujay Sundar
 hw05.cpp
 dynamic memory
*/

#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

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
	const string& getNobleName() const {return nobleName;}
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

//Function prototype to find the index of the noble pointer within the vector of Noble pointers. Takes in this vector (passed by constant reference) and the name of the noble (passed by constant reference)
size_t findNobleIndex(const vector<Noble*>& nobles, const string& nobleName);

//Function prototype to find the index of the warrior pointer within the vector of Warrior pointers. Takes in this vector (passed by constant reference) and the name of the warrior (passed by constant reference)
size_t findWarriorIndex(const vector<Warrior*>& warriors, const string& warriorName);


int main()
{
	//Opens the file 'nobleWarriors.txt'
    ifstream ifs("nobleWarriors.txt");
    if (!ifs) {
        cerr << "failed to open nobleWarriors.txt";
        exit(1);
    }

	//Defines several uninitialized variables in order to store certain strings from the file in each one
	string first_word;
	string nobleName1;
	string nobleName2;
	string warriorName;

	//Defines several uninitialized vectors
	vector<Noble*> nobles;
	vector<Warrior*> warriors;

	//Vector of Warrior pointers that contains all warriors that have been fired
	vector<Warrior*> unemployedWarriors;

	//Uninitialized variable that holds a warrior's strength (double)
	double warriorStrength;
	//Reads in first word of each line of the file
	 while (ifs >> first_word) {
	 	//If the first word is Warrior
		if (first_word == "Warrior") {
			//Read the second word on that line as the warrior's name and the third word as the warrior's strength
			ifs >> warriorName >> warriorStrength;
			//Add a new Warrior onto the heap and add it into the vector of Warrior pointers
			warriors.push_back(new Warrior(warriorName, warriorStrength));
		//If the first word is Noble
		} else if (first_word == "Noble") {
			//Read the second word on that line as the noble's name
			ifs >> nobleName1;
			//Add a new Noble onto the heap and add it into the vector of Noble pointers
			nobles.push_back(new Noble(nobleName1));
		//If the first word is Hire
		} else if (first_word == "Hire") {
			//Read the second word on that line as the noble's name and the next word as the warrior's name
			ifs >> nobleName1 >> warriorName;
			//Define an index variable and assign the return of a findNobleIndex call to it
			size_t index1 = findNobleIndex(nobles, nobleName1);

			//Define another index variable and assign the return of a findWarriorIndex call to it
			size_t index2 = findWarriorIndex(warriors, warriorName);
			//Print an error message if both indices are out of bounds
			if (index1 == nobles.size() || index2 == warriors.size()) {
				cerr << "Index not found" << endl;;
			} else {
				//Or else, access the noble at the index1 index and have them hire the warrior at the index2 index
				nobles[index1]->hire(*warriors[index2]);
			}
		//If the first word is Fire
		} else if (first_word == "Fire") {
			//Read the second word in the file as the noble's name and the third word as the warrior's name
			ifs >> nobleName1 >> warriorName;

			//Define an index variable and assign the return of a findNobleIndex call to it
			size_t i = findNobleIndex(nobles, nobleName1);

			//Define another index variable and assign the return of a findWarriorIndex call to it
			size_t j = findWarriorIndex(warriors, warriorName);

			//Print an error message if both indices are out of bounds
			if (i == nobles.size() && j == warriors.size()) {
				cerr << "Index not found";
			} else {
				//Or else, access the noble at the index1 index and have them hire the warrior at the index2 index
				nobles[i]->fire(*warriors[j]);
			}
		//If the first word is Battle
		} else if (first_word == "Battle") {
			//Read the second word as the noble's name of the first noble and the third word as the noble's name of
			//the second noble.
			ifs >> nobleName1 >> nobleName2;
			//Define an index variable and assign the return of a findNobleIndex call to it
			size_t index1 = findNobleIndex(nobles, nobleName1);

			//Define another index variable and assign the return of a findNobleIndex call to it
			size_t index2 = findNobleIndex(nobles, nobleName2);
			//Access the noble at the index1 index and have them hire the noble at the index2 index
			nobles[index1]->battle(*nobles[index2]);
		} else if (first_word == "Status") {
			cout << "Status" << endl;
			cout << "======" << endl;
			cout << "Nobles: " << endl;
			//Displays the output of each noble pointer in the 'nobles' vector using the output operator
			for (size_t i = 0; i < nobles.size(); ++i) {
				cout << *nobles[i] << endl;
			}

			for (size_t i = 0; i < warriors.size(); ++i) {
				//If the warrior pointer at that index has been fired
				if (warriors[i]->getWarriorJobStatus() == false) {
					//Add that warrior pointer into the vector of fired warrior pointers
					unemployedWarriors.push_back(warriors[i]);
					cout << "Unemployed Warriors: " << endl;
					//Displays the output of each warrior pointer in the 'warriors' vector using the output operator
					cout << *warriors[i] << endl;
				}
			}
			//If either the 'nobles' or 'warriors' vectors are empty, display "NONE"
			if (nobles.empty()) {
				cout << "NONE" << endl;
			}
			if (warriors.empty()) {
				cout << "Unemployed Warriors: " << endl << "NONE" << endl;
			}
		//If the first word is Clear
		} else if (first_word == "Clear") {
			//Delete each noble pointer from the heap
			for (size_t i = 0; i < nobles.size(); ++i) {
				delete nobles[i];
			}
			//Delete each warrior pointer from the heap
			for (size_t i = 0; i < warriors.size(); ++i) {
				delete warriors[i];
			}
			//Clear both vectors' contents
			nobles.clear();
			warriors.clear();
		}
	 }
	//Close the file
    ifs.close();
    return 0;
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

