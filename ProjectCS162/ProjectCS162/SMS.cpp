#include "SMS.hpp"


void StudentManagementSystem::Reload() {
	system("md Data\\Class");
	system("md Data\\Student");
	system("md Data\\Course");
    //acclist.Reload();
    //classlist.Reload();
}

void StudentManagementSystem::ImportClass() {
    // Get info of class here
	string Class = "18APCS1.csv";
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

void StudentManagementSystem::CreateAcademicYear()
{
	// get info
	string tmp = "2018-2019";

	//
	courselist.CreateAcademicYear(tmp);
}

void StudentManagementSystem::CreateSemester()
{
	/*
		display the AcademicYear to choose
			ifstream in("Data\\AcademicYear.txt");
			...
		get info
	*/
	string name = "2018-2019";
	/*
		enter a semester to create
	*/
	string sem = "Fall";
	
	courselist.CreateSemester(name, sem);
}

void StudentManagementSystem::DeleteAcademicYear()
{
	/*
		display
		choose a year
	*/
	string name = "2018-2019";

	courselist.DeleteAcademicYear(name);
}

void StudentManagementSystem::DeleteSemester()
{
	/*
		show Academic year
		choose
		name = "2018-2019"

		show Semester
		choose 
		sem = "Fall"
	*/
	string name = "2018-2019";
	string sem = "Fall";

	courselist.DeleteSemester(name, sem);
}

void StudentManagementSystem::ImportCourse()
{
	/*
		get info of the year
		get info of the semester
		get info of the course to import
	*/
	string year = "2018-2019";
	string sem = "Fall";
	string name = "Course1.csv";

	courselist.ImportCourse(year, sem, name);
}

void StudentManagementSystem::Run()
{
	Reload();
	//CreateAcademicYear();
	//CreateSemester();
	//DeleteAcademicYear();
	//DeleteSemester();
	//ImportClass();
	//ChangeClassOfStudent();
	ImportCourse();
//	Main_menu();
}


