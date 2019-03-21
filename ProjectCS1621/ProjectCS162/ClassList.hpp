#ifndef ClassList_hpp
#define ClassList_hpp

#include "Class.hpp"

class ClassList {
private:
    vector<string> listClass;
public:
    void AddClass(string Class);
	void AddStudent(Student student);
    void RemoveStudent(Student student);
    void Reload();
    void SaveData();
    string ViewList(); // Return a student is chosen
};
#endif // ClassList_hpp