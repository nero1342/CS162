#ifndef SMS_hpp
#define SMS_hpp

#include "AccountList.hpp"
#include "ClassList.hpp"

class StudentManagementSystem {
private:
    AccountList acclist;
    ClassList classlist;
public:
    void Reload();
    void ImportClass();
    void AddNewStudent();
    void EditExistStudent();
    void RemoveStudent();
    void ChangeClassOfStudent();
    void ViewListClasses();
    void ViewListStudentsOfClass();
};
#endif // SMS_hpp