#include "SMS.hpp"


void StudentManagementSystem::Reload() {
    acclist.Reload();
    classlist.Reload();
}

void StudentManagementSystem::ImportClass() {
    // Get info of class here
    string Class;

    // 
    acclist.ImportClass(Class);
    classlist.AddClass(Class);
    acclist.SaveData();
    classlist.SaveData();
}

void StudentManagementSystem::AddNewStudent() {
    // Get info of student here
    Student student;
    
    //
    acclist.Add(student);
    classlist.AddStudent(student);
    acclist.SaveData();
    classlist.SaveData();
}
