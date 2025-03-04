/*
  Sujay Sundar
  rec08.cpp
  Cyclic association and copy control
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Student;
class Course {
    friend ostream& operator<<(ostream& os, const Course& course);
public:
    Course(const string& courseName);
    const string& getName() const;
    bool addStudent(Student* student);
    void removeStudentsFromCourse();
private:
    string courseName;
    vector<Student*> students;
};

class Student {
    friend ostream& operator<<(ostream& os, const Student& student);
public:
    Student(const string& studentName);
    const string& getName() const;
    bool addCourse(Course* course);
    void removedFromCourse(Course* course);
private:
    string studentName;
    vector<Course*> courses;
};

class Registrar {
    friend ostream& operator<<(ostream& os, const Registrar& regist);
public:
    Registrar();
    bool addCourse(const string& courseName);
    bool addStudent(const string& studentName);
    bool enrollStudentInCourse(const string& studentName, const string& courseName);
    bool cancelCourse(const string& courseName);
    void purge();
private:
    size_t findStudent(const string& studentName) const;
    size_t findCourse(const string& courseName) const;
    vector<Course*> courses;
    vector<Student*> students;
};

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

Course::Course(const string& courseName) : courseName(courseName) {}
const string& Course::getName() const {return courseName;}
bool Course::addStudent(Student* student) {
    for (size_t i = 0; i < students.size(); ++i) {
        if (students[i] == student) {
            return false;
        }
    }
    students.push_back(student);
    return true;
}

void Course::removeStudentsFromCourse() {
    for (size_t i = 0; i < students.size(); ++i) {
        students[i]->removedFromCourse(this);
    }
    while (!students.empty()) {
        students.pop_back();
    }
}

ostream& operator<<(ostream& os, const Course& course) {
    os << course.courseName << ": ";
    if (course.students.empty()) {
        os << "No Students";
    } else {
        for (size_t i = 0; i < course.students.size(); ++i) {
            os << course.students[i]->getName() << " ";
        }
    }
    return os;
}

Student::Student(const string& studentName) : studentName(studentName) {}
const string& Student::getName() const {return studentName;}
bool Student::addCourse(Course* course) {
    for (const Course* c : courses) {
        if (c == course) {
            return false;
        }
    }
    courses.push_back(course);
    return true;
}

void Student::removedFromCourse(Course* course) {
    size_t removeI = courses.size();
    for (size_t i = 0; i < courses.size(); ++i) {
        if (courses[i] == course) {
            removeI = i;
        }
    }
    if (removeI < courses.size()) {
        for (size_t i = removeI; i < courses.size() - 1; ++i) {
            courses[i] = courses[i+1];
        }
        courses.pop_back();
    }
}

ostream& operator<<(ostream& os, const Student& student) {
    os << student.studentName << ": ";
    if (student.courses.empty()) {
        os << "No courses";
    } else {
        for (size_t i = 0; i < student.courses.size(); ++i) {
            os << student.courses[i]->getName() << " ";
        }
    }
    return os;
}

Registrar::Registrar() {}
    bool Registrar::addCourse(const string& courseName) {
        if (findCourse(courseName) != courses.size()) {
            return false;
        }
        courses.push_back(new Course(courseName));
        return true;
    }

    bool Registrar::addStudent(const string& studentName) {
        if (findStudent(studentName) != students.size()) {
            return false;
        }
        students.push_back(new Student(studentName));
        return true;
    }

    bool Registrar::enrollStudentInCourse(const string& studentName, const string& courseName) {
        size_t studentI = findStudent(studentName);
        size_t courseI = findCourse(courseName);
        if (studentI == students.size() || courseI == courses.size()) {
            return false;
        }
        Student* student = students[studentI];
        Course* course = courses[courseI];
        if (!student->addCourse(course) || !course->addStudent(student)) {
            return false;
        }
        return true;
    }

    bool Registrar::cancelCourse(const string& courseName) {
        size_t courseI = findCourse(courseName);
        if (courseI == courses.size()) {
            return false;
        }
        courses[courseI]->removeStudentsFromCourse();
        delete courses[courseI];
        for (size_t i = courseI; i < courses.size() - 1; ++i) {
            courses[i] = courses[i+1];
        }
        courses.pop_back();
        return true;
    }

    void Registrar::purge() {
        while (!courses.empty()) {
            delete courses[courses.size() - 1];
            courses.pop_back();
        }
        while (!students.empty()) {
            delete students[students.size() - 1];
            students.pop_back();
        }
    }

    size_t Registrar::findStudent(const string& studentName) const {
        for (size_t i = 0; i < students.size(); ++i) {
            if (students[i]->getName() == studentName) {
                return i;
            }
        }
        return students.size();
    }

    size_t Registrar::findCourse(const string& courseName) const {
        for (size_t i = 0; i < courses.size(); ++i) {
            if (courses[i]->getName() == courseName) {
                return i;
            }
        }
        return courses.size();
    }

    ostream& operator<<(ostream& os, const Registrar& regist) {
        os << "Registrar's Report" << endl << "Courses:" << endl;
        for (size_t i = 0; i < regist.courses.size(); ++i) {
            os << *regist.courses[i] << endl;
        }
        os << "Students:" << endl;
        for (size_t i = 0; i < regist.students.size(); ++i) {
            os << *regist.students[i] << endl;
        }
        return os;
    }
