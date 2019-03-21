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
	string GetName();
	void Import();
    void Reload();
    void Add(Student student);
    void Remove(Student student);
    string ViewList();

    void SaveData();
};

#endif // Class_hpp