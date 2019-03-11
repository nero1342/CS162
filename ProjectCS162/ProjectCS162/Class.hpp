#ifndef Class_hpp
#define Class_hpp

#include "STL.hpp"
#include "Student.hpp"

class Class{
private:
    vector<Student> list;
public:
    void Add(Student student);
    void Remove(Student student);
    void ViewList();
};

#endif // Class_hpp