#include "SMS.hpp"


void StudentManagementSystem::Reload() {
	system("md Data\\Class");
	system("md Data\\Student");
	system("md Data\\Course");
	system("md Data\\Export");
	system("md Data\\Lecturer");
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
			if (filename == "" || filename == "." || filename == "..") continue;
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
	Class myClass;
	myClass.SetName(classlist.ViewList());
	if (myClass.GetName() == "RETURN") return;
	// Get info of student here
	Student student;
	student.SetStudentID("");
	student.SetClass(myClass.GetName());
	NewStudentInfo(student);
	if (student.getStudentID() == "") return;
	//
	acclist.Reload();
	acclist.Add(student);
	acclist.SaveData();
	classlist.AddStudent(student);
}

void StudentManagementSystem::EditExistStudent(){
	Class myClass;
	myClass.SetName(classlist.ViewList());
	if (myClass.GetName() == "RETURN") return;
	Student student;
	student.SetStudentID(myClass.ViewList());
	if (student.getStudentID() == "RETURN") return;
	student.Reload();
	EditInfo(student);
	// cai nay cung khong can
	// class cuoi cung chi luu ID lai thoi
	//
	student.SaveData();
}

void StudentManagementSystem::RemoveStudent() {
	// Get info of student here
    Class myClass;
	myClass.SetName(classlist.ViewList());
	if (myClass.GetName() == "RETURN") return;
	Student student;
	Student t = student;
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
	string year = "2018-2019";
	menu Menu;
	Menu.title = "NEW ACADEMIC YEAR INFOMATION";
	Menu.name.clear();
	Menu.name = { "Year:",
				"Apply",
				"Cancel"
	};
	Menu.minchosen = 1;
	Menu.chosen = 1;
	vector<string> answer;
	answer.clear();
	for (int i = 1; i <= 1; i++) answer.push_back("");
	if (fill_menu(Menu, answer) == 0) return;
	year = answer[0];
	courselist.CreateAcademicYear(year);
}

void StudentManagementSystem::CreateSemester()
{
	string year = ViewAcademicYear();
	if (year == "RETURN") return;

	menu Menu;
	Menu.title = "NEW SEMESTER INFOMATION";
	Menu.name.clear();
	Menu.name = { "Semester:",
				"Apply",
				"Cancel"
	};
	Menu.minchosen = 1;
	Menu.chosen = 1;
	vector<string> answer;
	answer.clear();
	for (int i = 1; i <= 1; i++) answer.push_back("");
	if (fill_menu(Menu, answer) == 0) return;
	string sem = answer[0];
	courselist.CreateSemester(year, sem);
}

void StudentManagementSystem::DeleteAcademicYear()
{
	string year = ViewAcademicYear();
	if (year == "RETURN") return;
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
	ifstream fin("Data\\Course\\" + year + "\\Semester.txt");
	string st;
	while (getline(fin, st)) {
		list.push_back(st);
	}
	list.push_back("RETURN");
	menu Menu(year + "- SEMESTER", list, 1);
	return menu_choose(Menu);
}

void StudentManagementSystem::ImportScoreboard()
{
	Lecturer lecturer(AccountLogin.getUsername());
	lecturer.Reload();
	menu courseMenu("COURSES OF " + lecturer.getName(), lecturer.getListCourse(), 1);
	string courseID = menu_choose(courseMenu);
	if (courseID == "RETURN") return;

	vector<string> scoreboard = ListFileInDicrectory("*.csv");
	menu import_menu("Choose class", scoreboard, 1);
	string nameScoreboard = menu_choose(import_menu);
	if (nameScoreboard == "RETURN") return;

	//CourseID format: year//sem//courseID, splitted below
	string year, sem;
	reverse(courseID.begin(), courseID.end());
	while (courseID.back() != '\\') year.push_back(courseID.back()), courseID.pop_back();
	courseID.pop_back();
	while (courseID.back() != '\\') sem.push_back(courseID.back()), courseID.pop_back();
	courseID.pop_back();
	reverse(courseID.begin(), courseID.end());
	reverse(sem.begin(), sem.end());
	reverse(year.begin(), year.end());
	//

	Scoreboard a;
	a.ImportScoreboard(year, sem, courseID, nameScoreboard);
}

void StudentManagementSystem::ExportScoreboard()
{
	string year, sem;
	string courseID = ViewCourse(year, sem);
	if (courseID == "RETURN") return;

	Scoreboard a;
	if (a.ExportScoreboard(year, sem, courseID))
		Message("Export scoreboard succeeded");
	else Message("Export scoreboard failed");
}

void StudentManagementSystem::ExportAttendaceList()
{
	string year, sem;
	string courseID = ViewCourse(year, sem);
	if (courseID == "RETURN") return;
	AttendanceList a;
	a.Reload("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + "-attendancelist.txt");
	a.ExportAttend(courseID);
	Message("Export scoreboard succeeded");
}

void StudentManagementSystem::ViewScoreboard()
{
	string year, sem, courseID = ViewCourse(year, sem);
	if (courseID == "RETURN") return;
	Scoreboard score;
	if (!score.Reload("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + "-scoreboard.txt")) 
		Message("You have no scoreboard here!!");
	else score.View();
}

void StudentManagementSystem::ViewAttendanceList()
{
	string year, sem, courseID = ViewCourse(year, sem);
	if (courseID == "RETURN") return;
	AttendanceList a;
	a.Reload("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + "-attendancelist.txt");
	a.View();
}


void StudentManagementSystem::CreateNewLecturer()
{

}

void StudentManagementSystem::ViewAllLecturers()
{
	vector<string> listLecturer = ListFileInDicrectory("Data\\Lecturer\\*.txt");
	for (string & lecturer : listLecturer) {
		if (lecturer == "RETURN") continue;
		while (!lecturer.empty() && lecturer.back() != '.') lecturer.pop_back();
		if (!lecturer.empty()) lecturer.pop_back();
	}
	menu import_menu("VIEW ALL LECTURERS", listLecturer, 1);
	while (menu_choose(import_menu) != "RETURN");
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
	while (true) {
		string year = ViewAcademicYear();
		if (year == "RETURN") break;
		while (true) {
			string sem = ViewSemester(year);
			if (sem == "RETURN") break;
			
			// Show info new Course here
			Course tmp;
			tmp.SetID("");
			tmp.NewCourseInfo();
			if (tmp.GetCourseID() == "") return;
			//
			courselist.Load(year, sem);
			courselist.AddCourse(year, sem, tmp);
			courselist.Save(year, sem);
			return; 
		}
	}
	
}

void StudentManagementSystem::EditCourse()
{
	string year, sem;
	string courseID = ViewCourse(year, sem);
	if (courseID == "RETURN") return;
	courseID = "Data\\Course\\" + year + "\\" + sem + "\\" + courseID + ".txt";
	ifstream in(courseID);
	Course Change;
	Change.Reload(in);
	in.close();
	// Edit course here
	/*
				
	*/
	ofstream ou(courseID);
	Change.SaveData(ou);
	ou.close();
}

void StudentManagementSystem::RemoveCourse()
{
	string year, sem;
	string courseID = ViewCourse(year, sem);
	if (courseID == "RETURN") return;
	courselist.RemoveCourse(year, sem, courseID);
}

void StudentManagementSystem::AddAStudentToCourse()
{
	string year, sem;
	string courseID = ViewCourse(year, sem);
	if (courseID == "RETURN") return;
	Course course;
	ifstream in("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + ".txt");
	course.Reload(in);
	in.close();
				
	// Choose student from Class
	Class myClass;
	myClass.SetName(classlist.ViewList());
	if (myClass.GetName() == "RETURN") return;
	Student student;
	Student t = student;
	student.SetStudentID(myClass.ViewList());
	if (student.getStudentID() == "RETURN") return;
	student.Reload();
				
	//Add student to course, add attendance here
	course.AddNewStudent(student);
	ofstream ou("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + ".txt");
	course.SaveData(ou);
	ou.close();

	AttendanceList x;
	x.Reload("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + "-attendancelist.txt");
	x.AddStudent(student);
	x.SaveData("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + "-attendancelist.txt");

	return;	
}

void StudentManagementSystem::RemoveAStudentFromCourse()
{
	string year, sem;
	string courseID = ViewCourse(year, sem);
	if (courseID == "RETURN") return;
	Course course;
	ifstream in("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + ".txt");
	course.Reload(in);
	in.close();
				
	Student student;
	student.SetStudentID(course.ViewListStudent());
	if (student.getStudentID() == "RETURN") return;
	student.Reload();
	student.RemoveCourse(courseID);
	student.SaveData();

	AttendanceList a;
	a.Reload("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + "-attendancelist.txt");
	a.Remove(student.getStudentID());
	a.SaveData("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + "-attendancelist.txt");

	course.RemoveStudent(student.getStudentID());
	ofstream ou("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + ".txt");
	course.SaveData(ou);
	ou.close();	
}

string StudentManagementSystem::ViewListCourse(string year, string semester)
{
	// Return a course ID
	vector<string> list;
	ifstream fin("Data\\Course\\" + year + "\\" + semester + "\\CourseList.txt");
	string st;
	while (getline(fin, st)) {
		list.push_back(st);
	}
	list.push_back("RETURN");
	menu Menu(year + " - " + semester + " - COURSE", list, 1);
	return menu_choose(Menu);
}

string StudentManagementSystem::ViewCourse(string &year, string &semester)
{
	while (true) {
		year = ViewAcademicYear();
		if (year == "RETURN") break;
		while (true) {
			semester = ViewSemester(year);
			if (semester == "RETURN") break;
			while (true) {
				string courseID = ViewListCourse(year, semester);
				if (courseID == "RETURN") break;
				return courseID;
			}
		}
	}
	return "RETURN";
}

string StudentManagementSystem::ViewListStudentInCourse()
{
	string year, sem;
	string courseID = ViewCourse(year, sem);
	if (courseID == "RETURN") return "";
	Course course;
	ifstream in("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + ".txt");
	course.Reload(in);
	in.close();

	Student student;
	while (true) {
		student.SetStudentID(course.ViewListStudent());
		if (student.getStudentID() == "RETURN") return "RETURN";
	}
}

void StudentManagementSystem::Lecturer_ViewCourse() {
	Lecturer lecturer(AccountLogin.getUsername());
	lecturer.Reload();
	menu courseMenu("COURSES OF " + lecturer.getName(), lecturer.getListCourse(), 1);
	string courseID = menu_choose(courseMenu);
	if (courseID == "RETURN") return;

	ifstream in("Data\\Course\\" + courseID + ".txt");
	Course course;
	course.Reload(in);
	in.close();

	Student student;
	while (true) {
		student.SetStudentID(course.ViewListStudent());
		if (student.getStudentID() == "RETURN") return;
	}
}

void StudentManagementSystem::Lecturer_ViewAttendance() {
	Lecturer lecturer(AccountLogin.getUsername());
	lecturer.Reload();
	menu courseMenu("COURSES OF " + lecturer.getName(), lecturer.getListCourse(), 1);
	string courseID = menu_choose(courseMenu);
	if (courseID == "RETURN") return;

	AttendanceList a;
	a.Reload("Data\\Course\\" + courseID + "-attendancelist.txt");
	a.View();
}

void StudentManagementSystem::Lecturer_ViewScoreboard() {
	Lecturer lecturer(AccountLogin.getUsername());
	lecturer.Reload();
	menu courseMenu("COURSES OF " + lecturer.getName(), lecturer.getListCourse(), 1);
	string courseID = menu_choose(courseMenu);
	if (courseID == "RETURN") return;

	//Show scoreboard of courseID here
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
		if (choose == "ADD NEW COURSE") AddACourse();
		if (choose == "EDIT EXIST COURSE") EditCourse();
		if (choose == "REMOVE COURSE") RemoveCourse();
		if (choose == "ADD STUDENT TO COURSE") AddAStudentToCourse();
		if (choose == "REMOVE STUDENT FROM COURSE") RemoveAStudentFromCourse();
		if (choose == "VIEW LIST OF COURSE") ViewListStudentInCourse();
		if (choose == "VIEW ATTENDANCE OF COURSE") ViewAttendanceList();
		if (choose == "CREATE NEW LECTURER") CreateNewLecturer();
		if (choose == "VIEW ALL LECTURERS") ViewAllLecturers();
	// SCOREBOARD
	if (choose == "SCOREBOARD") {
		menu sb_menu("STAFF MENU - SCOREBOARD", mf.SCOREBOARD_MENU, 1);
		Menu(sb_menu);
	}
		if (choose == "VIEW SCOREBOARD") ViewScoreboard();
		if (choose == "EXPORT SCOREBOARD") ExportScoreboard();
	// ATTENDANCE LIST
	if (choose == "ATTENDANCE LIST") {
		menu attendance_menu("STAFF MENU - ATTENDANCE LIST", mf.ATTENDANCE_MENU, 1);
		Menu(attendance_menu);
	}
		if (choose == "VIEW ATTENDANCE LIST") ViewAttendanceList();
		if (choose == "EXPORT ATTENDANCE LIST") ExportAttendaceList();
// STUDENT

// LECTURER
	if (choose == "VIEW LIST OF COURSES") Lecturer_ViewCourse();
	if (choose == "VIEW ATTENDANCE LIST OF A COURSE") Lecturer_ViewAttendance();
	if (choose == "EDIT AN ATTENDANCE");
	if (choose == "IMPORT SCOREBOARD OF A COURSE") ImportScoreboard();
	if (choose == "EDIT GRADE OF A STUDENT");
	if (choose == "VIEW A SCOREBOARD") Lecturer_ViewScoreboard();
}

void StudentManagementSystem::Run()
{
	MenuFunction mf;
	Reload();
	acclist.Reload();
	while (1) {
		menu main_menu;

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
	//ImportScoreboard();
	//ExportScoreboard();
}

