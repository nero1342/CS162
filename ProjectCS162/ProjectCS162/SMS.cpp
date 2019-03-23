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

vector<string> ListFileInDicrectory(string pattern) {
	vector<string> result;
	WIN32_FIND_DATA data;
	HANDLE hFind;
	if ((hFind = FindFirstFile(pattern.c_str(), &data)) != INVALID_HANDLE_VALUE) {
		do {
			string filename = data.cFileName;
			if (filename == "." || filename == "..") continue;
			result.push_back(filename);
		} while (FindNextFile(hFind, &data) != 0);
		FindClose(hFind);
	}
	result.push_back("RETURN");
	return result;
}

void StudentManagementSystem::ImportClass() {
	vector<string> listClass = ListFileInDicrectory("*.csv");
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
	while (true) {
		string result = myClass.ViewList();
		if (result == "RETURN") break;
	}
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
	string year = ViewAcademicYear();
	if (year == "RETURN") return;

	/*
		enter a semester to create
	*/
	string sem = "Fall";
	
	courselist.CreateSemester(year, sem);
}

void StudentManagementSystem::DeleteAcademicYear()
{
	/*
		display
		choose a year
	*/
	string year = ViewAcademicYear();
	if (year == "RETURN") return;

	//string name = "2018-2019";
	courselist.DeleteAcademicYear(year);
}

void StudentManagementSystem::DeleteSemester()
{
	while (true) {
		string year = ViewAcademicYear();
		if (year == "RETURN") return;
		string sem = ViewSemester(year);
		if (sem == "RETURN") continue;
		courselist.DeleteSemester(year, sem);
		return;
	}
}

string StudentManagementSystem::ViewAcademicYear()
{
	// Return a academic year
	vector<string> list;
	ifstream fin("Data\\AcademicYear.txt");
	string st;
	while (getline(fin, st)) {
		list.push_back(st);
	}
	list.push_back("RETURN");
	menu Menu("ACADEMIC YEAR", list, 1);
	return menu_choose(Menu);
}

string StudentManagementSystem::ViewSemester(string year)
{
	// Return a semester of a academic year
	vector<string> list;
	ifstream fin("Data\\" + year + "Semester.txt");
	string st;
	while (getline(fin, st)) {
		list.push_back(st);
	}
	list.push_back("RETURN");
	menu Menu(year + "- SEMESTER", list, 1);
	return menu_choose(Menu);
}

void StudentManagementSystem::ImportCourse()
{
	/*
		get info of the year
		get info of the semester
		get info of the course to import
	*/
	while (true) {
		string year = ViewAcademicYear();
		if (year == "RETURN") return;
		while (true) {
			string sem = ViewSemester(year);
			if (sem == "RETURN") break;
			while (true) {
				vector<string> listCourse = ListFileInDicrectory("*.csv");
				menu import_menu("Choose class", listCourse, 1);
				string CourseID = menu_choose(import_menu);
				if (CourseID == "RETURN") return;
				courselist.ImportCourse(year, sem, CourseID);
				return;
			}
		}
	}
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
	string year = "2018-2019";
	string sem = "Fall";
	string name = "CM101";
	*/
	string year, sem, name;
	while (true) {
		// Choose year

		while (true) {
			// Choose semester
			while (true) {
				// Chose Course ID
			}
		}
	}
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

string StudentManagementSystem::ViewListCourse(string year, string semester)
{
	// Return a course ID
	vector<string> list;
	ifstream fin("Data\\" + year + "\\" + semester + "\\CourseList.txt");
	string st;
	while (getline(fin, st)) {
		list.push_back(st);
	}
	list.push_back("RETURN");
	menu Menu(year + " - " + semester + " - COURSE", list, 1);
	return menu_choose(Menu);
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
	// CLASS
	if (choose == "CLASS") {
		menu class_menu("STAFF MENU - CLASS", mf.CLASS_MENU, 1);
		Menu(class_menu);
	}
		if (choose == "IMPORT CLASS") ImportClass();
		if (choose == "ADD NEW STUDENT") AddNewStudent();
		if (choose == "EDIT EXIST STUDENT") EditExistStudent();
		if (choose == "REMOVE A STUDENT") RemoveStudent();
		if (choose == "CHANGE CLASS OF STUDENT") ChangeClassOfStudent();
		if (choose == "VIEW LIST OF CLASSES") ViewListClasses();
	// COURSES
	if (choose == "COURSES") {
		menu courses_menu("STAFF MENU - COURSES", mf.COURSES_MENU, 1);
		Menu(courses_menu);
	}
		if (choose == "CREATE ACADEMIC YEAR") CreateAcademicYear();
		if (choose == "DELETE ACADEMIC YEAR") DeleteAcademicYear();
		if (choose == "CREATE SEMESTER") CreateSemester();
		if (choose == "DELETE SEMESTER") DeleteSemester();
		if (choose == "IMPORT COURSE") ImportCourse();
		if (choose == "ADD NEW COURSE");
		if (choose == "EDIT EXIST COURSE");
		if (choose == "REMOVE COURSE");
		if (choose == "REMOVE STUDENT FROM COURSE");
		if (choose == "ADD STUDENT");
	// SCOREBOARD
	if (choose == "SCOREBOARD") {
		menu sb_menu("STAFF MENU - SCOREBOARD", mf.SCOREBOARD_MENU, 1);
		Menu(sb_menu);
	}
	// ATTENDANCE LIST
	if (choose == "ATTENDANCE LIST") {
		menu attendance_menu("STAFF MENU - ATTENDANCE LIST", mf.ATTENDANCE_MENU, 1);
		Menu(attendance_menu);
	}
// STUDENT

// LECTURER

}

void StudentManagementSystem::Run()
{
	MenuFunction mf;
	menu main_menu;
	Reload();
	acclist.Reload();
	while (1) {
		login Log;
		string accountLogin = Log.login_menu(acclist);
		AccountLogin = acclist.Find(accountLogin);
		if (AccountLogin.getType() == "Staff") {
			main_menu.Assign("STAFF MENU", mf.STAFF_MENU, 1);
		}
		if (AccountLogin.getType() == "Student") {
			main_menu.Assign("STUDENT MENU", mf.STUDENT_MENU, 1);
		}
		if (AccountLogin.getType() == "Lecturer") {
			main_menu.Assign("LECTURER MENU", mf.LECTURER_MENU, 1);
		}	
		Menu(main_menu);
	}
}


