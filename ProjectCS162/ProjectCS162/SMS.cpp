#include "SMS.hpp"


void StudentManagementSystem::Reload() {
	system("md Data\\Class");
	system("md Data\\Student");
	system("md Data\\Course");
	system("md Data\\Export");
	acclist.Reload();
	acclist.Add(Account("admin", "admin", "Staff", "Staff"));
	acclist.SaveData();
    //acclist.Reload();
    //classlist.Reload();
}

void StudentManagementSystem::ImportClass() {
	// Get info of class here
	string pattern = "*.csv";
	vector<string> listClass;
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			string filename = data.cFileName;
			listClass.push_back(filename);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
	menu import_menu("Choose class", listClass, 1);
	string Class = menu_choose(import_menu);
	if (Class == "RETURN") return;

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

void StudentManagementSystem::EditExistStudent()
{
}

void StudentManagementSystem::RemoveStudent() {
	// Get info of student here
    Class myClass;
	myClass.SetName(classlist.ViewList());
	if (myClass.GetName() == "RETURN") return;
	Student student;
	student.SetStudentID(myClass.ViewList());
	if (student.getStudentID() == "RETURN") return;
	student.Reload();
	//
	acclist.Reload();
	acclist.Remove(student.getStudentID());
	classlist.RemoveStudent(student);
}

void StudentManagementSystem::ChangeClassOfStudent() {
    // Get info of student here
	Class myClass;
	myClass.SetName(classlist.ViewList());
	if (myClass.GetName() == "RETURN") return;
	Student student;
	student.SetStudentID(myClass.ViewList());
	if (student.getStudentID() == "RETURN") return;
	student.Reload();
    // Get name of new class
    string newClass = classlist.ViewList();
	if (newClass == "RETURN") return;
    //
    classlist.RemoveStudent(student);
    student.SetClass(newClass);
    classlist.AddStudent(student);
	acclist.Reload();
    acclist.Edit(student);
    acclist.SaveData();
}

void StudentManagementSystem::ViewListClasses()
{
	Class myClass;
	myClass.SetName(classlist.ViewList());
	if (myClass.GetName() == "RETURN") {
		return;
	}
	myClass.ViewList();
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

void StudentManagementSystem::ImportScoreboard()
{
	/*
		choose scoreboard
		choose year 
		choose semester
		choose course
	*/
	string name = "scoreboard.csv";
	string year = "2018-2019";
	string sem = "Fall";
	string course = "CM101";

	Import(name, "Data\\Course\\" + year + "\\" + sem + "\\");

	while (name.back() != '.') name.pop_back();
	name += "txt";

	year = "rename Data\\Course\\" + year + "\\" + sem + "\\" + name + " " + course + "-scoreboard.txt"; 
	system(year.c_str());
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

void StudentManagementSystem::Menu(menu &main_menu) {
	while (1) {
		string choose = menu_choose(main_menu);
		if (choose == "LOGOUT" || choose == "RETURN") {
			break;
		}
		Do(choose);
	}
}


void StudentManagementSystem::Do(string &choose) {
	// STAFF
	MenuFunction mf;
	if (choose == "CLASS") {
		menu class_menu("STAFF MENU", mf.CLASS_MENU, 1);
		Menu(class_menu);
	}
	// CLASS
	if (choose == "IMPORT CLASS") ImportClass();
	if (choose == "ADD NEW STUDENT") AddNewStudent();
	if (choose == "EDIT EXIST STUDENT") EditExistStudent();
	if (choose == "REMOVE A STUDENT") RemoveStudent();
	if (choose == "CHANGE CLASS OF STUDENT") ChangeClassOfStudent();
	if (choose == "VIEW LIST OF CLASSES") ViewListClasses();
	// COURSES

	// SCOREBOARD

	// ATTENDANCE LIST

// STUDENT

// LECTURER

}

void StudentManagementSystem::Run()
{
	/*MenuFunction mf;
	Reload();
	acclist.Reload();
	while (1) {
		login Log;
		string accountLogin = Log.login_menu(acclist);
		AccountLogin = acclist.Find(accountLogin);

		if (AccountLogin.getType() == "Staff") {
			menu main_menu("STAFF MENU", mf.STAFF_MENU, 1);
			Menu(main_menu);
		}
		if (AccountLogin.getType() == "Student") {
			menu main_menu("STUDENT MENU", mf.STUDENT_MENU, 1);
			Menu(main_menu);
		}
		if (AccountLogin.getType() == "Lecturer") {
			menu main_menu("LECTURER MENU", mf.LECTURER_MENU, 1);
			Menu(main_menu);
		}	
	}*/
	Reload();
	CreateAcademicYear();
	CreateSemester();
	ImportScoreboard();
}


