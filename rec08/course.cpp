#include "course.h"

#include <ostream>

#include "student.h"
using namespace std;

namespace BrooklynPoly {
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
}