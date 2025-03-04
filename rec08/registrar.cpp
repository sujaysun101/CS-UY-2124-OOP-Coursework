#include "registrar.h"

using namespace std;


namespace BrooklynPoly {
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
}