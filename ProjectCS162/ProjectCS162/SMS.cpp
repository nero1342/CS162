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


void StudentManagementSystem::ChangePassWord()
{
	menu Menu;
	Menu.title = "CHANGE ACCOUNT PASSWORD";
	Menu.name.clear();
	Menu.name = {
				 "Old Password:",
				 "New Password:",
				 "Confirm Password:",
				 "Apply",
				 "Cancel"
	};
	Menu.minchosen = 1;
	Menu.chosen = 1;
	Menu.maxLengthInfo = 30;
	vector<string > answer;
	answer.clear();
	answer.push_back("");
	answer.push_back("");
	answer.push_back("");
	while (true) {
		if (fill_menu(Menu, answer, 1) == 0) return;
		string oldPass = answer[0];
		string newPass = answer[1];
		string confirmNewPass = answer[2];
		if (!AccountLogin.Login(AccountLogin.getUsername(), oldPass)) {
			Message("Invalid current password.");
			continue;
		}
		if (newPass != confirmNewPass) {
			Message("Confirmation mismatched.");
			continue;
		}
		AccountLogin.ChangePassword(newPass);
		acclist.ChangePass(AccountLogin.getUsername(), newPass);
		Message("Change password successfully.");
		return;
	}
}

void StudentManagementSystem::ImportClass() {
	vector<string> listClass = ListFileInDicrectory("*.csv");
	menu import_menu("Choose class", listClass, 1);
	string Class = menu_choose(import_menu);
	if (Class == "RETURN") return;

	// 
	acclist.ImportClass(Class);
	classlist.AddClass(Class);
	Message("Import class successfully.");
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
	Message("Add student " + student.getStudentID() + " to class " + myClass.GetName() + " successfully.");
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
	student.SaveData();
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

	// Remove this student in all course he enrolled
	Course course;
	vector<string> courseList = student.GetCourse();
	for (auto i : courseList)
	{
		ifstream in("Data\\Course\\" + i + ".txt");
		course.Reload(in);
		in.close();
		course.RemoveStudent(student.getStudentID());

		ofstream ou("Data\\Course\\" + i + ".txt");
		course.SaveData(ou);
		ou.close();

		AttendanceList attendanceList;
		attendanceList.Reload("Data\\Course\\" + i + "-attendancelist.txt");
		attendanceList.Remove(student.getStudentID());
		attendanceList.SaveData("Data\\Course\\" + i + "-attendancelist.txt");
	}
	Message("Remove student " + student.getStudentID() + " out of class succesfully");
}

void StudentManagementSystem::ChangeClassOfStudent() {
    // Get info of student here
	Class myClass;
	//Message("Choose class of student need to change class");
	myClass.SetName(classlist.ViewList());
	if (myClass.GetName() == "RETURN") return;
	Student student;
	student.SetStudentID(myClass.ViewList());
	if (student.getStudentID() == "RETURN") return;
	student.Reload();
    // Get name of new class
	Message("Choose new class for this student");
    string newClass = classlist.ViewList();
	if (newClass == "RETURN") return;
    //
    classlist.RemoveStudent(student);
    student.SetClass(newClass);
    classlist.AddStudent(student);
	acclist.Reload();
    acclist.Edit(student);
    acclist.SaveData();
	Message("Changed " + student.getStudentID() + " from class " + myClass.GetName() + " to class " + newClass + " successfully.");
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
	Menu.maxLengthInfo = 30;
	vector<string> answer;
	answer.clear();
	for (int i = 1; i <= 1; i++) answer.push_back("");
	if (fill_menu(Menu, answer) == 0) return;
	year = answer[0];
	courselist.CreateAcademicYear(year);
	Message("Create Academic Year succesfully.");
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
	Menu.maxLengthInfo = 30;
	vector<string> answer;
	answer.clear();
	for (int i = 1; i <= 1; i++) answer.push_back("");
	if (fill_menu(Menu, answer) == 0) return;
	string sem = answer[0];
	courselist.CreateSemester(year, sem);
	Message("Create Semester successfully.");
}

void StudentManagementSystem::DeleteAcademicYear()
{
	string year = ViewAcademicYear();
	if (year == "RETURN") return;
	courselist.DeleteAcademicYear(year);
	Message("Delete Academic Year successfully.");
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
	Message("Delete Semester successfully.");
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
	/*menu courseMenu("COURSES OF " + lecturer.getName(), lecturer.getListCourse(), 1);
	string courseID = menu_choose(courseMenu);*/
	string courseID = lecturer.ViewCourse();
	if (courseID == "RETURN") return;

	vector<string> scoreboard = ListFileInDicrectory("*.csv");
	menu import_menu("Choose scoreboard", scoreboard, 1);
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
	//

	Scoreboard a;
	a.ImportScoreboard(year, sem, courseID, nameScoreboard);
	Message("Import Scoreboard successfully.");
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
	AttendanceList attendanceList;
	attendanceList.Reload("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + "-attendancelist.txt");
	attendanceList.ExportAttend(courseID);
	Message("Export scoreboard succeeded");
}

void StudentManagementSystem::ViewScoreboard()
{
	string year, sem, courseID = ViewCourse(year, sem);
	if (courseID == "RETURN") return;
	Scoreboard score;
	if (!score.Reload("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + "-scoreboard.txt")) 
		Message("You have no scoreboard here!!");
	else score.View(courseID);
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
	// get info
	menu Menu;
	Menu.title = "NEW LECTURER INFOMATION";
	Menu.name.clear();
	Menu.name = { "Name:",
				"Apply",
				"Cancel"
	};
	Menu.minchosen = 1;
	Menu.chosen = 1;
	Menu.maxLengthInfo = 30;
	vector<string> answer;
	answer.clear();
	for (int i = 1; i <= 1; i++) answer.push_back("");

	if (fill_menu(Menu, answer) == 0) return;

	Lecturer lecturer(answer[0]);
	lecturer.SaveData();
	acclist.Reload();
	acclist.Add(lecturer); //Them account cho no
	acclist.SaveData();
	Message("Create New Lecturer succesfully.");
}

void StudentManagementSystem::ViewAllLecturers()
{
	vector<string> listLecturer = ListFileInDicrectory("Data\\Lecturer\\*.txt");
	int cnt = 0;
	for (string & lecturer : listLecturer) {
		if (lecturer == "RETURN") continue;
		++cnt;
		lecturer = to_string(cnt) + ". " + lecturer;
		while (!lecturer.empty() && lecturer.back() != '.') lecturer.pop_back();
		if (!lecturer.empty()) lecturer.pop_back();
	}
	menu import_menu("VIEW ALL LECTURERS", listLecturer, 1);
	while (menu_choose(import_menu) != "RETURN");
}

void StudentManagementSystem::ImportCourse()
{
	while (true) {
		string year = ViewAcademicYear();
		if (year == "RETURN") return;
		while (true) {
			string sem = ViewSemester(year);
			if (sem == "RETURN") break;
			while (true) {
				vector<string> listCourse = ListFileInDicrectory("*.csv");
				menu import_menu("Choose course", listCourse, 1);
				string CourseID = menu_choose(import_menu);
				if (CourseID == "RETURN") return;
				courselist.ImportCourse(year, sem, CourseID);
				return;
			}
		}
	}
	Message("Import course successfully.");
}


void StudentManagementSystem::AddACourse()
{
	while (true) {
		string year = ViewAcademicYear();
		if (year == "RETURN") break;
		while (true) {
			string sem = ViewSemester(year);
			if (sem == "RETURN") break;
			
			// Show info new Course here
			Course tmp;
			tmp.SetID("");
			tmp.SetYear(year);
			tmp.SetSemester(sem);
			tmp.NewCourseInfo();
			if (tmp.GetCourseID() == "") return;
			//
			courselist.Load(year, sem);
			courselist.AddCourse(year, sem, tmp);
			courselist.Save(year, sem);
			Message("Add this course succesfully.");
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
	Change.EditCourseInfo();
	ofstream ou(courseID);
	Change.SaveData(ou);
	ou.close();
	Message("Edit this course successfully");
}

void StudentManagementSystem::RemoveCourse()
{

	string year, sem;
	string courseID = ViewCourse(year, sem);
	if (courseID == "RETURN") return;
	courselist.RemoveCourse(year, sem, courseID);
	Message("Remove this course successfully");
}

void StudentManagementSystem::AddAStudentToCourse()
{
	string year, sem;
	Message("Choose course you want to add student");
	string courseID = ViewCourse(year, sem);
	if (courseID == "RETURN") return;
	Course course;
	//course.SetYear(year);
	//course.SetSemester(sem);
	ifstream in("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + ".txt");
	course.Reload(in);
	in.close();
				
	// Choose student from Class
	Message("Choose student from existed classes to add to course");
	Class myClass;
	myClass.SetName(classlist.ViewList());
	if (myClass.GetName() == "RETURN") return;
	Student student;
	Student t = student;
	student.SetStudentID(myClass.ViewList());
	if (student.getStudentID() == "RETURN") return;
	student.Reload();
				
	//Add student to course, add attendance here
	student.AddCourse(year + "\\" + sem + "\\" + course.GetCourseID());
	student.SaveData();

	course.AddNewStudent(student);
	ofstream ou("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + ".txt");
	course.SaveData(ou);
	ou.close();

	AttendanceList x;
	x.Reload("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + "-attendancelist.txt");
	x.AddStudent(student);
	x.SaveData("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + "-attendancelist.txt");
	Message("Add student " + student.getStudentID() + " to course " + courseID + "successfully");
	return;	
}

void StudentManagementSystem::RemoveAStudentFromCourse()
{
	Message("Choose course you want to add student");
	string year, sem;
	string courseID = ViewCourse(year, sem);

	Course course(year, sem, courseID);

	Message("Choose student you want to remove from this course");

	Student student;
	student.SetStudentID(course.ViewListStudent());
	if (student.getStudentID() == "RETURN") return;
	student.Reload();
	string path = year + "\\" + sem + "\\" + courseID;
	student.RemoveCourse(path);
	student.SaveData();

	AttendanceList a;
	a.Reload("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + "-attendancelist.txt");
	a.Remove(student.getStudentID());
	a.SaveData("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + "-attendancelist.txt");

	course.RemoveStudent(student.getStudentID());
	ofstream ou("Data\\Course\\" + year + "\\" + sem + "\\" + courseID + ".txt");
	course.SaveData(ou);
	ou.close();	

	Message("Remove student " + student.getStudentID() + " from course " + courseID + "successfully");
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
	//list.push_back("RETURN");
	//menu Menu(year + " - " + semester + " - COURSE", list, 1);
	//return menu_choose(Menu);

	string title = year + " - " + semester + " - COURSE";
	stringstream ff;
	ff << left << setw(5) << "No"
		<< left << setw(30) << "Course ID"
		<< left << setw(30) << "Course Name"
		<< left << setw(15) << "Lecturer"
		<< left << setw(10) << "DOW"
		<< left << setw(12) << "Start Hour"
		<< left << setw(12) << "End Hour"
		<< left << setw(10) << "Room" << endl;

	string feature;
	getline(ff, feature);
	vector<string> schedule;
	schedule.push_back(feature);
	int cnt = 0;
	for (string courseID : list) {
		Course myCourse(year, semester, courseID);
		ff << left << setw(5) << ++cnt
			<< left << setw(30) << courseID
			<< left << setw(30) << myCourse.GetName()
			<< left << setw(15) << myCourse.GetLecturer()
			<< left << setw(10) << myCourse.GetDOW()
			<< left << setw(12) << myCourse.GetStartHour()
			<< left << setw(12) << myCourse.GetEndHour()
			<< left << setw(10) << myCourse.GetRoom() << endl;
		getline(ff, feature);
		schedule.push_back(feature);
	}
	schedule.push_back("RETURN");
	menu schedule_menu(title, schedule, 2);

	while (true) {
		string result = menu_choose(schedule_menu);
		if (result == "RETURN") return result;
		ff << result;
		int no;
		ff >> no;
		return list[no - 1];
	}
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

void StudentManagementSystem::Checkin()
{
	Student student(AccountLogin.getUsername());
	string studentID = student.getStudentID();
	string course = student.ViewSchedule();
	if (course == "RETURN") return;
	AttendanceList attendanceList;
	attendanceList.Reload("Data\\Course\\" + course + "-attendancelist.txt");
	if (attendanceList.EditAttend(student)) {
		attendanceList.SaveData("Data\\Course\\" + course + "-attendancelist.txt");
		Message("Check-in successfully");
	}
}

void StudentManagementSystem::EditAttend()
{
	Lecturer lecturer(AccountLogin.getUsername());
	lecturer.Reload();
	string courseID = lecturer.ViewCourse();
	if (courseID == "RETURN") return;

	ifstream in("Data\\Course\\" + courseID + ".txt");
	Course course;
	course.Reload(in);
	in.close();

	Student student;
	student.SetStudentID(course.ViewListStudent());
	student.Reload();
	if (student.getStudentID() == "RETURN") return;

	AttendanceList attendanceList;
	attendanceList.Reload("Data\\Course\\" + courseID + "-attendancelist.txt");
	if (attendanceList.EditAttend(student)) {
		attendanceList.SaveData("Data\\Course\\" + courseID + "-attendancelist.txt");
		Message("Edit attend of course " + courseID + "successfully");
	}
}

void StudentManagementSystem::EditGrade()
{
	Lecturer lecturer(AccountLogin.getUsername());
	lecturer.Reload();
	string courseID = lecturer.ViewCourse();
	if (courseID == "RETURN") return;

	ifstream in("Data\\Course\\" + courseID + ".txt");
	Course course;
	course.Reload(in);
	in.close();

	Student student;
	student.SetStudentID(course.ViewListStudent());
	if (student.getStudentID() == "RETURN") return;
	student.Reload();
	
	Scoreboard scoreboard;
	if (!scoreboard.Reload("Data\\Course\\" + courseID + "-scoreboard.txt"))
	{
		Message(" There is no scoreboard for this class");
		return;
	}
	if (scoreboard.EditGrade(student)) {
		Message("Edit grade of " + student.getStudentID() + " in course " + courseID + " successfully");
	}
	scoreboard.Save("Data\\Course\\" + courseID + "-scoreboard.txt");
}

void StudentManagementSystem::ViewCheckinResult()
{
	Student student(AccountLogin.getUsername());
	string studentID = student.getStudentID();
	string course = student.ViewSchedule();
	if (course == "RETURN") return;
	AttendanceList attendanceList;
	attendanceList.Reload("Data\\Course\\" + course + "-attendancelist.txt");
	vector<int> attend = attendanceList.GetAttend(studentID);
	vector<string> attendStatus;
	for (int i = 0; i < (int) attend.size(); ++i) {
		
		attendStatus.push_back("Week " + to_string(i + 1) + ": " + (attend[i] == 0 ? "It's not show time" : (attend[i] == 1 ? "Attend" : "Absent")));
	}
	attendStatus.push_back("RETURN");
	menu menuAttendStatus("ATTENDANCE OF " + student.getLastname() + ' '  + student.getFirstname() + " - " + studentID + " IN COURSE " + course, attendStatus, 1);
	while (menu_choose(menuAttendStatus) != "RETURN");
}

void StudentManagementSystem::Lecturer_ViewCourse() {
	Lecturer lecturer(AccountLogin.getUsername());
	lecturer.Reload();
	string courseID = lecturer.ViewCourse();
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

void StudentManagementSystem::Student_ViewSchedule()
{
	Student student(AccountLogin.getUsername());
	while (student.ViewSchedule() != "RETURN");

}

void StudentManagementSystem::Lecturer_ViewAttendance() {
	Lecturer lecturer(AccountLogin.getUsername());
	lecturer.Reload();
	string courseID = lecturer.ViewCourse();
	if (courseID == "RETURN") return;

	AttendanceList a;
	a.Reload("Data\\Course\\" + courseID + "-attendancelist.txt");
	a.View();
}


void StudentManagementSystem::Lecturer_ViewScoreboard() {
	Lecturer lecturer(AccountLogin.getUsername());
	lecturer.Reload();
	string courseID = lecturer.ViewCourse();
	if (courseID == "RETURN") return;

	//Show scoreboard of courseID here
	Scoreboard score;
	if (!score.Reload("Data\\Course\\" + courseID + "-scoreboard.txt"))
		Message("You have no scoreboard here!!");
	else score.View(courseID);
}

void StudentManagementSystem::Student_ViewScore()
{
	Student student(AccountLogin.getUsername());
	string studentID = student.getStudentID();
	string courseID = student.ViewSchedule();
	if (courseID == "RETURN") return;
	Scoreboard scoreboard;
	if (!scoreboard.Reload("Data\\Course\\" + courseID + "-scoreboard.txt"))
	{
		Message("This course has no score for you :'(");
		return;
	}
	vector<int> score = scoreboard.GetScore(studentID);

	stringstream ff;
	ff<< left << setw(20) << "Midterm"
		<< left << setw(20) << "Practice"
		<< left << setw(20) << "Final" << "\n";
	string feature;
	string course = "";
	for (int i = courseID.size() - 1; i >= 0; --i) {
		int ok = 0;
		if ((courseID[i] >= 'A'&&courseID[i] <= 'Z') ||
			(courseID[i] >= 'a'&&courseID[i] <= 'a') ||
			(courseID[i] >= '0'&&courseID[i] <= '9')) {
			course = courseID[i] + course;
			continue;
		}
		break;
	}
	menu student_score;
	student_score.minchosen = 2;
	student_score.chosen = 2;
	student_score.title = "SCORE OF " + studentID + " IN " + course;
	getline(ff, feature);
	student_score.name.clear();
	student_score.name.push_back(feature);
	ff << left << setw(20) << score[0]
		<< left << setw(20) << score[1]
		<< left << setw(20) << score[2] << "\n";
	getline(ff, feature);
	student_score.name.push_back(feature);
	student_score.name.push_back("RETURN");
	while (1) {
		string tmp = menu_choose(student_score);
		if (tmp == "RETURN") return;
	}
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
// COMMON
	if (choose == "VIEW PROFILE INFO") ViewProfile();
	if (choose == "CHANGE PASSWORD") ChangePassWord();
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
	if (choose == "CHECK-IN") Checkin();
	if (choose == "VIEW CHECK-IN RESULT") ViewCheckinResult();
	if (choose == "VIEW SCHEDULES") Student_ViewSchedule();
	if (choose == "VIEW SCORES OF A COURSE")Student_ViewScore();
// LECTURER
	if (choose == "VIEW LIST OF COURSES") Lecturer_ViewCourse();
	if (choose == "VIEW ATTENDANCE LIST OF A COURSE") Lecturer_ViewAttendance();
	if (choose == "EDIT AN ATTENDANCE") EditAttend();
	if (choose == "IMPORT SCOREBOARD OF A COURSE") ImportScoreboard();
	if (choose == "EDIT GRADE OF A STUDENT") EditGrade();
	if (choose == "VIEW A SCOREBOARD") Lecturer_ViewScoreboard();
}

void StudentManagementSystem::ViewProfile() {
	vector<string> myProfile;
	if (AccountLogin.getType() == "Student") {
		Student student(AccountLogin.getUsername());
		student.Reload();
		myProfile.push_back("Student ID: " + student.getStudentID());
		myProfile.push_back("Lastname: " + student.getLastname());
		myProfile.push_back("Firstname: " + student.getFirstname());
		myProfile.push_back("Gender: " + student.getGender());
		myProfile.push_back("Date of Birth: " + student.getDoB());
		myProfile.push_back("Class :" + student.getClass());
		myProfile.push_back("Type: Student");
	}
	else {
		myProfile.push_back("Name: " + AccountLogin.getUsername());
		myProfile.push_back("Type: " + AccountLogin.getType());
	}
	menu ViewProfileMenu("MY PROFILE", myProfile, 1);
	menu_choose(ViewProfileMenu);
}
void StudentManagementSystem::Run()
{
	MenuFunction mf;
	Reload();
	while (1) {
		menu main_menu;
		acclist.Reload();
		login Log;

		string accountLogin = Log.login_menu(acclist);
		AccountLogin = acclist.Find(accountLogin);
		if (AccountLogin.getType() == "Staff") {
			main_menu.Assign("STAFF MENU - " + accountLogin, mf.STAFF_MENU, 1);
		}
		if (AccountLogin.getType() == "Student") {
			main_menu.Assign("STUDENT MENU - " + accountLogin, mf.STUDENT_MENU, 1);
		}
		if (AccountLogin.getType() == "Lecturer") {
			main_menu.Assign("LECTURER MENU - " + accountLogin, mf.LECTURER_MENU, 1);
		}	
		Menu(main_menu);
	}
	//ImportScoreboard();
	//ExportScoreboard();
}

