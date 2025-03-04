/*
  Sujay Sundar
  rec05.cpp
 */

#include <chrono>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Section {
    friend ostream& operator<<(ostream& os, const Section& section);
public:
    Section(const string& sectionName, const string& day, int hour) : sectionName(sectionName), timeSlot(day, hour) {}
    const string& getSectionName() {return sectionName;}
    void addStudent(const string& sectionName) {
        students.push_back(new StudentRecord(sectionName));
    }
    void updateGrade(const string& studentName, int index, int grade) {
        for (StudentRecord* studentRecord : students) {
            if (studentRecord->getStudentName() == studentName) {
                studentRecord->setGrade(index, grade);
            }
        }
    }

    Section(const Section& section) : sectionName(section.sectionName), timeSlot(section.timeSlot) {
        for (const StudentRecord* studentRecord : section.students) {
            students.push_back(new StudentRecord(*studentRecord));
        }
    }

    ~Section() {
        cout << "Section " << sectionName << " is being deleted" << endl;
        for (size_t i = 0; i < students.size(); ++i) {
            cout << "Deleting " << students[i]->getStudentName() << endl;
            delete students[i];
        }
        students.clear();
    }

    friend ostream& operator<<(ostream& os, const Section& section) {
        os << "Section: " << section.sectionName << ", Time slot: " << section.timeSlot << ", Students:" << endl;
        for (const StudentRecord* studentRecord : section.students) {
            os << *studentRecord << endl;
        }
        return os;
    }

    class TimeSlot {
        friend ostream& operator<<(ostream& os, const TimeSlot& timeSlot);
    public:
        TimeSlot(const string& day, int hour) : day(day), hour(hour) {}
    private:
        string day;
        int hour;
    };

    friend ostream& operator<<(ostream& os, const TimeSlot& timeSlot) {
        string AM_or_PM = "am";
        int hour = timeSlot.hour;
        if (hour >= 12) {
            AM_or_PM = "pm";
            if (hour > 12) {
                hour = hour - 12;
            }
        } else if (hour == 0) {
            hour = 12;
        }
        os << "[Day: " << timeSlot.day << ", Start time: " << hour << AM_or_PM << "]";
        return os;
    }

    class StudentRecord {
        friend ostream& operator<<(ostream& os, const StudentRecord& student_record);
    public:
        StudentRecord(const string& studentName) : studentName(studentName), grades(14, -1) {}
        string getStudentName() const {return studentName;}
        void setGrade(int grade, int index) {
            if (index >= 1 && index <= 14) {
                grades[index - 1] = grade;
            }
        }

        friend ostream& operator<<(ostream& os, const StudentRecord& studentRecord) {
            os << "Name: " << studentRecord.studentName << ", Grades: ";
            for (int grade : studentRecord.grades) {
                os << grade << " ";
            }
            return os;
        }
    private:
        string studentName;
        vector<int> grades ;
    };

private:
    TimeSlot timeSlot;
    vector<StudentRecord*> students;
    string sectionName;
};

class LabWorker {
    friend ostream& operator<<(ostream& os, const LabWorker& labWorker);
public:
    LabWorker(const string& labWorkerName) : labWorkerName(labWorkerName) {}
    void addSection(Section& section) {
        this->section = &section;
    }
    void addGrade(const string& studentName, int index, int grade) {
        if (section != nullptr) {
            section->updateGrade(studentName, index, grade);
        }
    }

    friend ostream& operator<<(ostream& os, const LabWorker& labWorker) {
        os << labWorker.labWorkerName;
        if (labWorker.section) {
            os << " has " << *labWorker.section;
        } else {
            os << " does not have a section";
        }
        return os;
    }
private:
    string labWorkerName;
    Section* section;
};

// Test code
void doNothing(Section sec) { cout << sec << endl; }

int main()
{

    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe( "Moe" );
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection( secA2 );
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane( "Jane" );
    Section secB3( "B3", "Thursday", 11 );
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection( secB3 );
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
         << "those students (or rather their records?)\n";

    cout << "\nTest 9: Copy Constructor: make sure the following calls work:\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n" << secA2 << endl;

} // main
