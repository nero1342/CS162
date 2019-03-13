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

void StudentManagementSystem::RemoveStudent() {
    // Get info of student here
    Student student;

    //
    acclist.Remove(student.getStudentID());
    classlist.RemoveStudent(student);
    acclist.SaveData();
    classlist.SaveData();
}

void StudentManagementSystem::ChangeClassOfStudent() {
    // Get info of student here
    Student student;

    // Get name of new class
    string newClass;

    //
    classlist.RemoveStudent(student);
    student.SetClass(newClass);
    classlist.AddStudent(student);
    acclist.Edit(student);
    classlist.SaveData();
    acclist.SaveData();
}

void StudentManagementSystem::ImportCourse()
{
	// get info of course 


	
}
