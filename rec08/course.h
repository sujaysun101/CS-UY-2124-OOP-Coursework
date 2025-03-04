#ifndef course_h
#define course_h
#include <iostream>
#include <string>
#include <vector>

namespace BrooklynPoly {
    class Student;
    class Course {
        friend std::ostream& operator<<(std::ostream& os, const Course& course);
    public:
        Course(const std::string& courseName);
        const std::string& getName() const;
        bool addStudent(Student* student);
        void removeStudentsFromCourse();
    private:
        std::string courseName;
        std::vector<Student*> students;
    };
}
#endif