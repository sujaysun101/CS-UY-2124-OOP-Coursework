//Sujay Sundar

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;
/*
  rec01_start.cpp
  spring 2024
*/


//
// Function prototypes for tasks 15-17
//

// Task 15. Function to display a vector of ints



// Task 16. Function to modify the vector, using indices



// Task 17. Function to modify the vector, using a ranged for




//
// main
//
int main() { // Yes, it has to have an int for the return type
    //
    // Output
    //

    // Task 1. Printing hello ...  No use of "using namespace"

    std::cout << "Hello World!" << endl;

    // Task 2  Printing hello ...  Using "using namespace"

    cout << "Hello World!" << endl;

    //
    // Types and variables
    //

    // Task 3  Displaying uninitialized variable

    int x;
    //cout << "x: " << x << endl;

    // Task 4 Use the sizeof function to see the size in bytes of
    //        different types on your machine.

    int y = 17;
    int z = 2000000017;
    double pie = 3.14159;
    cout << "Size of x: " << sizeof(x) << endl;
    cout << "Size of y: " << sizeof(y) << endl;
    cout << "Size of z: " << sizeof(z) << endl;
    cout << "Size of pie: " << sizeof(pie) << endl;

    // Task 5  Attempt to assign the wrong type of thing to a variable

    //x = "felix";


    //
    // Conditions
    //

    // Task 6  Testing for a range


    if (y >= 10 && y <= 20) {
        cout << y << " is between 10 and 20, inclusive." << endl;
    } else {
        cout << y << " is not between 10 and 20, inclusive." << endl;
    }


    //
    // Loops and files
    //

    // Task 7  Looping, printing values 10 to 20 inclusive

    // First with a for loop

    for (int i = 10; i <= 20; ++i) {
        cout << i << "\t" ;
    }
    cout << endl;

    // Then with a while loop

    int i = 10;
    while (i <= 20) {
        cout << i << "\t";
        ++i;
    }
    cout << endl;

    // Finally with a do-while loop

    i = 10;
    do {
        cout << i << "\t";
        ++i;
    } while (i <= 20);
    cout << endl;

    // Task 8  Looping to successfully open a file, asking user for the name

    string filename;
    ifstream ifs;
    do {
        cout << "Please enter a filename: ";
        cin >> filename;
        ifs.open(filename);
        if (!ifs) {
            cerr << "failed to open " << filename;
        }
    } while (!ifs);


    // Task 9  Looping, reading file word by "word".

    ifstream jab;
    jab.open("text.txt");
    if (!jab) {
        cerr << "failed to open text.txt";
        exit(1);
    } else {
        string word;
        while (jab >> word) {
            cout << word << endl;
        }
        jab.close();
    }


    // Task 10 Open a file of integers, read it in, and display the sum.

    ifstream jab2;
    jab2.open("integers.txt");
    if (!jab2) {
        cerr << "failed to open integers.txt";
        exit(1);
    } else {
        int number;
        int total = 0;
        while (jab2 >> number) {
            total += number;
        }
        cout << total << endl;
        jab2.close();
    }

    // Task 11 Open and read a file of integers and words. Display the sum.

    ifstream jab3;
    jab2.open("mixed.txt");
    if (!jab2) {
        cerr << "failed to open mixed.txt";
        exit(1);
    } else {
        int number;
        int total = 0;
        while (jab3 >> number) {
            total += number;
        }
        cout << total << endl;
        jab3.close();
    }


    //
    // Vectors
    //

    // Task 12 Filling a vector of ints

    vector<int> vectorOfInts;
    for (int i = 10; i <= 100; i += 2) {
        vectorOfInts.push_back(i);
    }

    //cout << vectorOfInts[0] << ' ' << vectorOfInts[1];

    // Task 13 Displaying the vector THREE times
    //         a) using the indices,

    for (size_t i = 0; i < vectorOfInts.size(); ++i) {
        cout << vectorOfInts[i] << "\t";
    }
    cout << endl;

    //         b) using a "ranged for"

    for (int x : vectorOfInts) {
        cout << x << "\t";
    }
    cout << endl;

    //         c) using indices again but backwards

    for (size_t i = vectorOfInts.size() - 1; i < vectorOfInts.size(); --i) {
        cout << vectorOfInts[i] << "\t";
    }

    // Task 14. Initialize a vector with the primes less than 20.

    vector<int> vectorOfPrimesLessThanTwenty = {2, 3, 5, 7, 11, 13, 17, 19};
    for (size_t i = 0; i < vectorOfPrimesLessThanTwenty.size(); ++i) {
        cout << vectorOfPrimesLessThanTwenty[i] << "\t";
    }

    //
    // Function calls
    //

    // Task 15  Function to print a vector


    // Task 16  Function to double the values in a vector


    // Task 17  Function to double the values in a vector, using a ranged for


}

//
// Function definitions for tasks 15-17
//

// Task 15. Function to display a vector of ints



// Task 16. Function to modify the vector, using indices



// Task 17. Function to modify the vector, using a ranged for


