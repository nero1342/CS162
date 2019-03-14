#ifndef ClassList_hpp
#define ClassList_hpp

#include "Class.hpp"

class ClassList {
private:
    map<string, Class> listClass;
public:
    void AddClass(string Class);
    void AddStudent(Student student);
    void RemoveStudent(Student student);
    void Reload();
    void SaveData();
    void ViewList();
};
#endif // ClassList_hpp