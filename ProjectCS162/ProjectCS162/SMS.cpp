#include "SMS.hpp"


void StudentManagementSystem::Reload() {
	system("md Data\\Class");
	system("md Data\\Student");
    //acclist.Reload();
    //classlist.Reload();
}

void StudentManagementSystem::ImportClass() {
    // Get info of class here
	string Class = "Class-2.csv";
	// 
    acclist.ImportClass(Class);
	classlist.AddClass(Class);
}

void StudentManagementSystem::AddNewStudent() {
    // Get info of student here
    Student student;
    
    //
	acclist.Reload();
    acclist.Add(student);
	acclist.SaveData();

	classlist.AddStudent(student);
}

void StudentManagementSystem::RemoveStudent() {
	// Get info of student here
    Student student;

    //
	acclist.Reload();
	acclist.Remove(student.getStudentID());

	classlist.RemoveStudent(student);
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
	acclist.Reload();
    acclist.Edit(student);
    acclist.SaveData();
}

void StudentManagementSystem::Run()
{
	Reload();
	ImportClass();
//	Main_menu();
}


