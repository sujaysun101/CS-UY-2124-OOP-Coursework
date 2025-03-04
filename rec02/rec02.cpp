//Sujay Sundar

#include <iostream>
#include <vector>
#include <fstream>

using namespace std;

struct Hydrocarbon {
    vector<string> names;
    int carbon;
    int hydrogen;
};

void openFile (ifstream& ifs);

void fillVector(vector<Hydrocarbon>& hydrocarbons, ifstream& ifs);

void displayHydrocarbon (const vector<Hydrocarbon>& hydrocarbons);

void printHydrocarbon (const Hydrocarbon& hydrocarbon);

void sortVector (vector<Hydrocarbon>& hydrocarbons);

void insertHydrocarbon (vector<Hydrocarbon>& hydrocarbons, const string& name, int carbon, int hydrogen);

size_t findHydrocarbon (vector<Hydrocarbon>& hydrocarbon, int carbon, int hydrogen);

int main()
{
    ifstream ifs;
    vector<Hydrocarbon> hydrocarbon;
    openFile(ifs);
    fillVector(hydrocarbon, ifs);
    displayHydrocarbon(hydrocarbon);
    sortVector(hydrocarbon);
    displayHydrocarbon(hydrocarbon);

    return 0;
}

void openFile(ifstream& ifs) {
    string filename;
    do {
        cout << "Please enter a filename: ";
        cin >> filename;
        ifs.open(filename);
        if (!ifs) {
            cerr << "failed to open " << filename;
        }
    } while (!ifs);
}

void fillVector(vector<Hydrocarbon>& hydrocarbons, ifstream& ifs) {
    string name;
    int numOfCarbons;
    int numOfHydrogens;
    char character;

    while (ifs >> name >> character >> numOfCarbons >> character >> numOfHydrogens) {
        insertHydrocarbon(hydrocarbons, name, numOfCarbons, numOfHydrogens);
    }
}

size_t findHydrocarbon(const vector<Hydrocarbon>& hydrocarbon, int carbon, int hydrogen) {
    for (size_t i = 0; i < hydrocarbon.size(); ++i) {
        if (hydrocarbon[i].carbon == carbon && hydrocarbon[i].hydrogen == hydrogen) {
            return i;
        }
    }
    return hydrocarbon.size();
}

void insertHydrocarbon(vector<Hydrocarbon>& hydrocarbons, const string& name, int carbon, int hydrogen) {
    size_t i = findHydrocarbon(hydrocarbons, carbon, hydrogen);
    if (i == hydrocarbons.size()) {
        Hydrocarbon hydrocarbon;
        hydrocarbon.carbon = carbon;
        hydrocarbon.hydrogen = hydrogen;
        hydrocarbons.push_back(hydrocarbon);
        i = hydrocarbons.size() - 1;
    }
    hydrocarbons[i].names.push_back(name);
}

void printHydrocarbon(const Hydrocarbon& hydrocarbon) {
    cout << "C" << hydrocarbon.carbon << "H" << hydrocarbon.hydrogen;
    for (size_t i = 0; i < hydrocarbon.names.size(); ++i) {
        cout << hydrocarbon.names[i] << ' ';
    }
    cout << endl;
}

void displayHydrocarbon(const vector<Hydrocarbon>& hydrocarbons) {
    for (const Hydrocarbon& hydrocarbon : hydrocarbons) {
        printHydrocarbon(hydrocarbon);
    }
    cout << endl;
}

void sortVector(vector<Hydrocarbon>& hydrocarbons) {
    for (size_t i = 0; i < hydrocarbons.size(); ++i) {
        for (size_t j = 0; j < hydrocarbons.size(); ++j) {
            if (hydrocarbons[j].carbon > hydrocarbons[j+1].carbon) {
                Hydrocarbon temp = hydrocarbons[j];
                hydrocarbons[j] = hydrocarbons[j+1];
                hydrocarbons[j+1] = temp;
            }
            if (hydrocarbons[j].carbon == hydrocarbons[j+1].carbon) {
                if (hydrocarbons[j].hydrogen > hydrocarbons[j+1].hydrogen) {
                    Hydrocarbon temp = hydrocarbons[j];
                    hydrocarbons[j] = hydrocarbons[j+1];
                    hydrocarbons[j+1] = temp;
                }
            }
        }
    }
}









