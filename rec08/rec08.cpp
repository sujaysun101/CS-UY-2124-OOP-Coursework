/*
  Sujay Sundar
  rec08.cpp
  Cyclic association and copy control

  Starter Code for required functionality

  Yes, of course, you may add other methods.

  And no, this won't compile. You have to fix the cyclic association
  and implement the methods.

 */

#include <iostream>
#include <string>
#include <vector>
#include "registrar.h"
using namespace BrooklynPoly;
using namespace std;

int main()
{
    Registrar regist;

    cout << "No courses or students added yet\n";
    cout << regist << endl;

    cout << "AddCourse CS101.001\n";
    regist.addCourse("CS101.001");
    cout << regist << endl;

    cout << "AddStudent FritzTheCat\n";
    regist.addStudent("FritzTheCat");
    cout << regist << endl;

    cout << "AddCourse CS102.001\n";
    regist.addCourse("CS102.001");
    cout << regist << endl;

    cout << "EnrollStudentInCourse FritzTheCat CS102.001\n";
    regist.enrollStudentInCourse("FritzTheCat", "CS102.001");
    cout << "EnrollStudentInCourse FritzTheCat CS101.001\n";
    regist.enrollStudentInCourse("FritzTheCat", "CS101.001");
    cout << regist << endl;

    cout << "EnrollStudentInCourse Bullwinkle CS101.001\n";
    cout << "Should fail, i.e. do nothing, "
         << "since Bullwinkle is not a student.\n";
    regist.enrollStudentInCourse("Bullwinkle", "CS101.001");
    cout << regist << endl;

    cout << "CancelCourse CS102.001\n";
    regist.cancelCourse("CS102.001");
    cout << regist << endl;

    cout << "Purge for start of next semester\n";
    regist.purge();
    cout << regist << endl;
    return 0;
} // main

