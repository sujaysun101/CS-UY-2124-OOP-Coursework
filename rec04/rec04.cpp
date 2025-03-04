//Task 1
//Sujay Sundar
//rec04.cpp

#include <iostream>
#include <vector>

using namespace std;

//Task 16:
struct Complex {
    double real;
    double img;
};

//Task 17:
/*class PlainOldClass {
public:
    PlainOldClass() : x(-72) {}
    int getX() const { return x; }
    void setX( int val )  { x = val; }
private:
    int x;
};*/

//Task 18:
/*class PlainOldClassV2 {
public:
    PlainOldClassV2() : x(-72) {}
    int getX() const { return x; }
    void setX( int x )  { x = x; } // HMMMM???
private:
    int x;
};*/

class PlainOldClassV2 {
public:
    PlainOldClassV2() : x(-72) {}
    int getX() const { return x; }
    void setX( int x )  { this->x = x; } // No confusion!
private:
    int x;
};

//Task 28:
class Colour {
public:
    Colour(const string& name, unsigned r, unsigned g, unsigned b)
        : name(name), r(r), g(g), b(b) {}
    void display() const {
        cout << name << " (RBG: " << r << "," << g<< "," << b << ")";
    }
private:
    string name;      // what we call this colour
    unsigned r, g, b; // red/green/blue values for displaying
};

//Task 29: You cannot convert from 'const main()::SpeakerSystem*' to 'main()::SpeakerSystem*' Add a const definition to the private variable, to match both pointer types.
class SpeakerSystem {
public:
    void vibrateSpeakerCones(unsigned signal) const {

        cout << "Playing: " << signal << "Hz sound..." << endl;
        cout << "Buzz, buzzy, buzzer, bzap!!!\n";
    }
};

class Amplifier {
public:
    void attachSpeakers(const SpeakerSystem& spkrs)
    {
        if(attachedSpeakers) {
            cout << "already have speakers attached!\n";
        } else {
            attachedSpeakers = &spkrs;
        }
    }

    void detachSpeakers() { // should there be an "error" message if not attached?
        attachedSpeakers = nullptr;
    }

    void playMusic( ) const {
        if (attachedSpeakers) {
            attachedSpeakers -> vibrateSpeakerCones(440);
        } else {
            cout << "No speakers attached\n";
        }
    }
private:
    const SpeakerSystem* attachedSpeakers = nullptr;
};

//Task 30
class Person {
public:
    Person(const string& name) : name(name) {}
    void movesInWith(Person& newRoomate) {
        if (&newRoomate == this) {
            cerr << "roomates are the same person";
        } else if (roomie != nullptr) {
            cerr << "self already has roommate";
        } else if (newRoomate.roomie != nullptr) {
            cerr << "roomie already has roommate";
        } else {
            roomie = &newRoomate;        // now I have a new roomie
            newRoomate.roomie = this;    // and now they do too
        }

    }
    const string& getName() const { return name; }
    // Don't need to use getName() below, just there for you to use in debugging.
    const string& getRoomiesName() const { return roomie->getName(); }
private:
    Person* roomie = nullptr;
    string name;
};

int main() {
    //Task 2
    int x;
    x = 10; //Task 3: Watch displays x: 0
    //Task 4: Watch changes x: 0 to x: 10
    //Task 5: Watch displays x: 10
    cout << "x = " << x << endl;
    //Task 6: Watch displays 0x5ffe5c (memory address) using "&x"
    cout << 0xB << endl;
    cout << hex << 0xB << endl;
    cout << dec << 0xB << endl;
    //Task 7: Shows me the value of &x and the value stored at that memory location of x.
    //Task 8: Displays p: NULL
    int* p;
    p = &x;
    //Task 10:
    cout << "p = " << p << endl;

    //Task 9:
    //p = 0x5ffe5c; // using the value from my Watch window

    //Task 10:
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p contains " << *p << endl;

    //Task 11:
    *p = -2763;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "x now contains " << x << endl;

    //Task 12:
    int y(13);
    cout << "y contains " << y << endl;
    p = &y;
    cout << "p now points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    *p = 980;
    cout << "p points to where " << *p << " is stored\n";
    cout << "*p now contains " << *p << endl;
    cout << "y now contains " << y << endl;

    //Task 13:
    int* q;
    q = p;
    cout << "q points to where " << *q << " is stored\n";
    cout << "*q contains " << *q << endl;

    //Task 4: Lines 64 and 65
    double d(33.44);
    double* pD(&d);
    *pD = *p;
    *pD = 73.2343;
    *p  = *pD;
    *q  = *p;
    //pD  = p;
    //p   = pD;

    //Task 15:
    int joe = 24;
    const int sal = 19;
    int*  pI;
    //pI = &joe;
    //*pI = 234;
    //Line failed because you cannot convert a const int* to an int*
    //pI = &sal;

    //Line failed because you cannot convert an int to an int*
    //pI = 7623;

    //const int* pcI;
    //pcI = &joe;
    //Line failed because pcI is marked as a const, and the value of a const cannot be modified during program execution.
    //*pcI = 234;
    //pcI = &sal;
    //Line failed because pcI is marked as a const, and the value of a const cannot be modified during program execution.
    //*pcI = 7623;

    //Line failed because a type of cpI is not declared in front of it. In C++, if you want a constant pointer variable you must always declare it as "const (type)*"
    //int* const cpI;
    //Line failed because it was already declared in the previous line
    //int* const cpI(&joe);
    //Line failed because it was already declared in the previous 2 lines
    //int* const cpI(&sal);

    //Line failed because cpI is marked as a const, and the value of a const cannot be modified during program execution.
    //cpI = &joe;
    //*cpI = 234;
    //Line failed because cpI is marked as a const, and the value of a const cannot be modified during program execution.
    //cpI = &sal;
    //*cpI = 7623;

    //Line failed because a type of cpcI is not declared in front of it. In C++, if you want a constant pointer variable you must always declare it as "const (type)*"
    //const int* const cpcI;
    //Line failed because it was already declared in the previous line
    //const int* const cpcI(&joe);
    //Line failed because it was already declared in the previous line
    //const int* const cpcI(&sal);
    //Line failed because cpcI is marked as a const, and the value of a const cannot be modified during program execution.
    //cpcI = &joe;  // *cpcI = 234;
    //Line failed because cpcI is marked as a const, and the value of a const cannot be modified during program execution.
    //cpcI = &sal;
    //Line failed because cpcI is contained within a read-only location, which contains a const (unmodifiable) variable.
    //*cpcI = 7623;

    //Task 16:
    Complex c = {11.23,45.67};
    Complex* pC(&c);
    //cout << "real: " << *pC.real << "\nimaginary: " << *pC.img << endl;
    cout << "real: " << (*pC).real << "\nimaginary: " << (*pC).img << endl;
    cout << "real: " << pC->real << "\nimaginary: " << pC->img << endl;

    //Task 17:
    /*PlainOldClass poc;
    PlainOldClass* ppoc( &poc );
    cout << ppoc->getX() << endl;
    ppoc->setX( 2837 );
    cout << ppoc->getX() << endl;*/

    //Task 18:
    PlainOldClassV2 poc;
    PlainOldClassV2* ppoc( &poc );
    cout << ppoc->getX() << endl;
    ppoc->setX( 2837 );
    cout << ppoc->getX() << endl;

    //Task 19:
    int* pDyn = new int(3); // p points to an int initialized to 3 on the heap
    *pDyn = 17;
    cout << "The " << *pDyn
     << " is stored at address " << pDyn
     << " which is in the heap\n";

    //Task 20:
    cout << pDyn << endl;
    delete pDyn;
    cout << pDyn << endl;
    cout << "The 17 might STILL be stored at address " << pDyn<< " even though we deleted pDyn\n";
    cout << "But can we dereference pDyn?  We can try.  This might crash... " << *pDyn << ".  Still here?\n";

    //Task 21:
    pDyn = nullptr;
    double* pDouble = nullptr;

    //Task 22:
    //cout << "Can we dereference nullptr?  " << *pDyn << endl;
    //cout << "Can we dereference nullptr?  " << *pDouble << endl;

    //Task 23: this can be nullptr because it is a pointer that points to the address of an object a method is invoked on

    //Task 24:
    double* pTest = new double(12);
    delete pTest;
    pTest = nullptr;
    delete pTest; // safe

    //Task 25:
    short* pShrt = new short(5);
    delete pShrt; //Program executes with exit code of 0
    //delete pShrt; //Program runs into an error with a numerical exit code, because you try to delete pShrt twice.

    //Task 26:
    //long jumper = 12238743;
    //delete jumper;
    //long* ptrTolong = &jumper;
    //delete ptrTolong;  // What happens here? - Successfully deletes ptrTolong
    //Complex cmplx;
    //delete cmplx;      // What happens here? - Expected a pointer, but was provided an entire Struct to delete.

    //Task 27:
    vector<Complex*> complV; // can hold pointers to Complex objects
    Complex* tmpPCmplx;      // space for a Complex pointer
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        tmpPCmplx = new Complex; // create a new Complex object on the heap
        tmpPCmplx->real = ndx;   // set real and img to be the
        tmpPCmplx->img  = ndx;   // value of the current ndx
        complV.push_back(tmpPCmplx); // store the ADDRESS of the object in a vector or pointer to Complex
    }
    // display the objects using the pointers stored in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        cout << complV[ ndx ]->real << endl;
        cout << complV[ ndx ]->img  << endl;
    }
    // release the heap space pointed at by the pointers in the vector
    for (size_t ndx = 0; ndx < 3; ++ndx) {
        delete complV[ndx];
    }
    // clear the vector
    complV.clear();

    //Task 28:
    /*vector<Colour*> colours;
    string inputName;
    unsigned inputR, inputG, inputB;

    // fill vector with Colours from the file
    // this could be from an actual file but here we are using the keyboard instead of a file
    // (so we don't have to create an actual file)
    // Do you remember the keystroke combination to indicate "end of file" at the keyboard?
    // somehow the while's test has to fail - from keyboard input
    while (cin >> inputName >> inputR >> inputG >> inputB) {
        colours.push_back(new Colour(inputName, inputR, inputG, inputB));
    }

    // display all the Colours in the vector:
    for (size_t ndx = 0; ndx < colours.size(); ++ndx) {
        colours[ndx]->display();
        cout << endl;
    }

    for (size_t i = 0; i < 3; ++i) {
        delete complV[i];
    }

    complV.clear();
*/
    //Task 29: Above main
    SpeakerSystem speaker_system();
    Amplifier amp();

    //Task 30:
    // write code to model two people in this world
    Person joeBob("Joe Bob"), billyJane("Billy Jane");

    // now model these two becoming roommates
    joeBob.movesInWith(billyJane);

    // did this work out?
    cout << joeBob.getName() << " lives with " << joeBob.getRoomiesName() << endl;
    cout << billyJane.getName() << " lives with " << billyJane.getRoomiesName() << endl;

    return 0;
}
