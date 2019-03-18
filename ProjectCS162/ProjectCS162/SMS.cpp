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

	name = "Data\\Course\\" + name;
	vector<string> sems;
	string link = name + "\\Semester.txt";

	ifstream in(link);
	string x;
	while (in >> x)
	{
		if (x == sem)
		{
			in.close();
			return;
		}
		sems.push_back(x);
	}
	in.close();

	ofstream ou(link);
	for (auto i : sems) ou << i << '\n';
	ou << sem << '\n';
	ou.close();

	name = "md " + name + "\\" + sem;
	system(name.c_str());
}

void StudentManagementSystem::DeleteAcademicYear()
{
	/*
		display
		choose a year
	*/
	string name = "2018-2019";

	string link = "Data\\AcademicYear.txt";
	vector<string> year;
	string x;

	ifstream in(link);
	while (in >> x) year.push_back(x);
	in.close();

	for (int i = 0; i < year.size(); ++i) if (year[i] == name)
	{
		swap(year[i], year.back());
		year.pop_back();
	}

	ofstream ou(link);
	for (auto i : year) ou << i << '\n';
	ou.close();

	name = "rmdir /s /q Data\\Course\\" + name;
	system(name.c_str());
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

	name = "Data\\Course\\" + name;
	vector<string> sems;
	string link = name + "\\Semester.txt";
	string x;

	ifstream in(link);
	while (in >> x) sems.push_back(x);
	in.close();

	for (int i = 0; i < sems.size(); ++i) if (sems[i] == sem)
	{
		swap(sems[i], sems.back());
		sems.pop_back();
	}

	ofstream ou(link);
	for (auto i : sems) ou << i << '\n';
	ou.close();

	name = "rmdir /s /q " + name + "\\" + sem;
	system(name.c_str());
}

void StudentManagementSystem::Run()
{
	//CreateAcademicYear();
	//CreateSemester();
	//DeleteAcademicYear();
	DeleteSemester();
	//Reload();
	//ImportClass();
	//ChangeClassOfStudent();
//	Main_menu();
}


