#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

//Function prototype that takes in a string (passed by reference)
//representing an encrypted string and an int representing the rotation distance.
//It will take the string and modify it based on what the rotation distance is.
void modifyString(string& encryptedString, int dist);

//Function prototype that takes in a char representing an encrypted character
//and an int representing the rotation distance. It will take the character and
//return a new decrypted character based on what the rotation distance is.
char decryptedChar(char encryptedChar, int dist);

int main()
{
    //Created and initialized an empty vector. This vector will contain
    //each line of the file as a separate string.
    vector<string> lines;

    //Opens a file called 'encrypted.txt'.
    ifstream ifs;
    ifs.open("encrypted.txt");

    //If file does not open, error message is printed and program is exited.
    if (!ifs) {
        cerr << "failed to open encrypted.txt";
        exit(1);
    }

    //Created but uninitialized variable representing each line of the file.
    string line;

    //Created but uninitialized variable representing rotation distance.
    int dist;

    //First line of the file containing rotation distance assigned to 'dist' variable.
    ifs >> dist;

    while (getline(ifs, line)) { //Reads each line of the file.
        //Calls the 'modifyString' function. Takes in each line and the rotation
        //distance as arguments, while each line is read.
        modifyString(line, dist);

        //Adds the newly modified line to the vector.
        lines.push_back(line);
    }

    //File is closed after we are done with using it.
    ifs.close();

    //For loop for displaying all of 'lines' content BACKWARDS
    for (int i = lines.size() - 1; i > 0; --i) {
        if (i != 1) {
            cout << lines[i] << endl;
        } else {
            cout << lines[i];
        }
    }

    return 0;
}

char decryptedChar(char encryptedChar, int dist) {
    //Created a vector of chars containing all CAPITAL letter of the alphabet.
    vector<char> alpha = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O','P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

    //Created and uninitialized an int variable 'new_dist'
    int new_dist;

    //Switch the sign of 'dist', such that 'dist' is positive when moving backwards and negative when moving forwards.
    dist = 0 - dist;

    //If the rotation distance is a negative number, constantly add 26 to its current value,
    //until the distance becomes positive. For example, Instead of having to go forward
    //'-25' times, we can just add 26 and go backward one time.
    while (dist < 0) {
        dist = dist + 26;
    }

    //Update the distance to be the value of its modulus when divided by 26
    dist = dist % 26;

    for (size_t i = 0; i < alpha.size(); i++) {
        //If the current character in 'alpha' is equal to the passed-in argument,
        //update 'new_dist' value to the sum of the current index and the current distance.
        if (alpha[i] == encryptedChar) {
            new_dist = i + dist;
            break;
        }
    }

    //returns the character at the index of the modulus of the updated 'new_dist' when divided by 26.
    return alpha[new_dist % 26];
}

void modifyString(string& encryptedString, int dist) {
    for (int i = 0; i < encryptedString.size(); ++i) {
        //If the current character in the string is not a white space delimeter AND if the
        //current character is an alphabetical letter, then set the current character to the
        //character returned by the 'decryptedChar' function, when taking in the current
        //character and its rotational distance.
        if (encryptedString[i] != ' ' && isalpha(encryptedString[i])) {
            encryptedString[i] = decryptedChar(encryptedString[i], dist);
        }
    }
}


