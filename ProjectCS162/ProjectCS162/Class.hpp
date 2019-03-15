#ifndef Class_hpp
#define Class_hpp

#include "STL.hpp"
#include "Student.hpp"

class Class{
private:
    vector<Student> list;
    string name;
public:
    void SetName(string newName);
	void Import();
    void Reload();
    void Add(Student student);
    void Remove(Student student);
    void ViewList();

    void SaveData();
};

#endif // Class_hpp