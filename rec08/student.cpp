#include "student.h"

#include <ostream>

#include "course.h"

using namespace std;

namespace BrooklynPoly {
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
}