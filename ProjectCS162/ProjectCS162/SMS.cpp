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

void StudentManagementSystem::AddACourse()
{
	/*
		get info for the Course
		pass by ref
		Course tmp(....)
	*/
	Course tmp;
	string year = "2018-2019";
	string sem = "Fall";
	courselist.AddCourse(year,sem,tmp);
}

void StudentManagementSystem::EditCourse()
{
	/*
		get info for new course
		choose year and sem
		load vector course for edit
	*/
	string year = "2018-2019";
	string sem = "Fall";
	courselist.Load(year, sem);
	/*
		return a number of course in the vector to edit
	*/
	int chosen = 1;
	string tmp=courselist.GetCourse(chosen);
	tmp = "Data\\Course\\" + year + "\\" + sem + "\\" + tmp + ".txt";

	ifstream in(tmp);
	Course Change;
	Change.ReadInput(in);
	in.close();

	/*
		output to change
		Change.SetName(...)......
		......
	*/

	ofstream ou(tmp);
	Change.SaveData(ou);
	ou.close();
}

void StudentManagementSystem::RemoveCourse()
{
	/*
		get info
		choose year
		choose sem
	*/
	string year = "2018-2019";
	string sem = "Fall";
	string name = "CM101";

	courselist.RemoveCourse(year, sem, name);
}

void StudentManagementSystem::RemoveAStudentFromCourse()
{
	/*
		choose year 
		choose sem
		get info of the course (display the courselist)
	*/
	string year = "2018-2019";
	string sem = "Fall";
	string name = "CM101";

	Course course;
	ifstream in("Data\\Course\\" + year + "\\" + sem + "\\" + name + ".txt");
	course.ReadInput(in);
	in.close();

	/*
		show listOfStudent
	*/
	int chosen = 0;

	Student student;
	student.SetStudentID(course.GetStudentID(chosen));
	student.Reload();
	student.RemoveCourse(name);
	student.SaveData();

	course.RemoveStudent(chosen);
	ofstream ou("Data\\Course\\" + year + "\\" + sem + "\\" + name + ".txt");
	course.SaveData(ou);
	ou.close();
}

void StudentManagementSystem::Run()
{
	//Reload();
	//CreateAcademicYear();
	//CreateSemester();
	//DeleteAcademicYear();
	//DeleteSemester();
	//ImportClass();
	//ChangeClassOfStudent();
	//ImportCourse();
	//RemoveCourse();
	//RemoveAStudentFromCourse();
//	Main_menu();
}


