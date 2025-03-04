#ifndef student_h
#define student_h
#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly {
    class Course;
    class Student {
        friend std::ostream& operator<<(std::ostream& os, const Student& student);
    public:
        Student(const std::string& studentName);
        const std::string& getName() const;
        bool addCourse(Course* course);
        void removedFromCourse(Course* course);
    private:
        std::string studentName;
        std::vector<Course*> courses;
    };
}
#endif