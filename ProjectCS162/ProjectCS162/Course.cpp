#include "Course.h"
#include <sstream>
#include <iomanip>
#include "menu.h"
#include "control.h"


string Course::GetCourseID()
{
	return ID;
}

void Course::SetID(string name)
{
	ID = name;
}

void Course::SetName(string newname)
{
	name = newname;
}

void Course::SetClass(string newclass)
{
	Class = newclass;
}

void Course::SetLecturer(string newlecturer)
{
	lecturer = newlecturer;
}

void Course::SetStartDate(string newStartDate)
{
	startDate = newStartDate;
}

void Course::SetEndDate(string newEndDate)
{
	endDate = newEndDate;
}

void Course::SetDOW(string newDOW)
{
	dayOfWeek = newDOW;
}

void Course::SetStartHour(string newStartHour)
{
	startHour = newStartHour;
}

void Course::SetEndHour(string newEndHour)
{
	endHour = newEndHour;
}

void Course::SetRoom(string newRoom)
{
	room = newRoom;
}

void Course::NewCourseInfo() {
	menu Menu;
	Menu.title = "NEW COURSE INFOMATION";
	Menu.name.clear();
	Menu.name = { "CourseID:",
				"Name:",
				"Class:",
				"Lecturer:",
				"StartDate:",
				"EndDate:",
				"Day Of Week:",
				"Start Hour:",
				"End Hour:",
				"Room:",
				"Apply",
				"Cancel"
	};
	Menu.minchosen = 1;
	Menu.chosen = 1;
	Menu.maxLengthInfo = 30;
	vector<string> answer;
	answer.clear();
	for (int i = 1; i <= 10; i++) answer.push_back("");
	if (fill_menu(Menu, answer) == 0) return;
	else {
		SetID(answer[0]);
		SetName(answer[1]);
		SetClass(answer[2]);
		SetLecturer(answer[3]);
		SetStartDate(answer[4]);
		SetEndDate(answer[5]);
		SetDOW(answer[6]);
		SetStartHour(answer[7]);
		SetEndHour(answer[8]);
		SetRoom(answer[9]);
		return;
	}

}


void Course::EditCourseInfo() {
	menu Menu;
	Menu.title = "EDIT " + GetCourseID() + " INFOMATION";
	Menu.name.clear();
	Menu.name = { 
			//	"Course ID:",
				"Name:",
				"Class:",
				"Lecturer:",
				"StartDate:",
				"EndDate:",
				"Day Of Week:",
				"Start Hour:",
				"End Hour:",
				"Room:",
				"Apply",
				"Cancel"
	};
	Menu.maxLengthInfo = 30;
	Menu.minchosen = 1;
	Menu.chosen = 1;
	vector<string > answer;
	answer.clear();

	answer.push_back(GetName());
	answer.push_back(GetClass());
	answer.push_back(GetLecturer());
	answer.push_back(GetStartDate());
	answer.push_back(GetEndDate());
	answer.push_back(GetDOW());
	answer.push_back(GetStartHour());
	answer.push_back(GetEndHour());
	answer.push_back(GetRoom());
	if (fill_menu(Menu, answer) == 0) return;
	else {
		SetName(answer[0]);
		SetClass(answer[1]);
		SetLecturer(answer[2]);
		SetStartDate(answer[3]);
		SetEndDate(answer[4]);
		SetDOW(answer[5]);
		SetStartHour(answer[6]);
		SetEndHour(answer[7]);
		SetRoom(answer[8]);
		return;
	}
}
void Course::Reload(istream & in)
{
	listOfStudent.clear();
	getline(in, ID);
	getline(in, name);
	getline(in, Class);
	getline(in, lecturer);
	getline(in, startDate);
	getline(in, endDate);
	getline(in, dayOfWeek);
	getline(in, startHour);
	getline(in, endHour);
	getline(in, room);
	string x;
	while (in >> x) listOfStudent.push_back(x);
}

void Course::ReadInput(istream & in)
{
	getline(in, ID);
	getline(in, name);
	getline(in, Class);
	getline(in, lecturer);
	getline(in, startDate);
	getline(in, endDate);
	getline(in, dayOfWeek);
	getline(in, startHour);
	getline(in, endHour);
	getline(in, room);
}


void Course::SaveData(ofstream & ou)
{
	ou << ID << "\n";
	ou << name << "\n";
	ou << Class << "\n";
	ou << lecturer << "\n";
	ou << startDate << "\n";
	ou << endDate << "\n";
	ou << dayOfWeek << "\n";
	ou << startHour << "\n";
	ou << endHour << "\n";
	ou << room << "\n";
	for (auto i : listOfStudent) ou << i << '\n';
}

void Course::Import()
{
	ifstream in("Data\\Class\\" + Class + ".txt");
	string tmp;
	vector<string> studentlist;
	while (in >> tmp) studentlist.push_back(tmp);
	in.close();

	Student x;
	for (auto i : studentlist)
	{
		x.SetStudentID(i);
		listOfStudent.push_back(x.getStudentID());
		x.Reload();
		x.AddCourse(year + "\\" + semester + "\\" + ID);
		x.SaveData();
	}

}

void Course::CreateAccountForLecturer()
{
	Lecturer lect(lecturer);
	AccountList acclist;
	acclist.Reload();
	acclist.Add(lect);
	acclist.SaveData();
	//
	lect.Reload();
	lect.AddCourse(year + "\\" + semester + "\\" + ID);
	lect.SaveData();
}

void Course::DeleteCourse()
{
	for (string studentID : listOfStudent)
	{
		Student student(studentID);
		string courseID = year + "\\" + semester + "\\" + ID;
		student.RemoveCourse(courseID);
		student.SaveData();
	}
	Lecturer tmpLecturer(lecturer);
	tmpLecturer.Reload();
	tmpLecturer.DeleteCourse(year + "\\" + semester + "\\" + ID);
	tmpLecturer.SaveData();
}

void Course::AddNewStudent(Student & x)
{
	for (auto i : listOfStudent) if (i == x.getStudentID()) return;
	listOfStudent.push_back(x.getStudentID());
}

string Course::ViewListStudent() {
	string title = "STUDENT LIST OF" + name;
	vector<string> matrix_class;
	stringstream ff;

	ff << left << setw(5) << "No"
		<< left << setw(15) << "Student ID"
		<< left << setw(30) << "Lastname"
		<< left << setw(10) << "Firstname"
		<< left << setw(10) << "Gender"
		<< left << setw(15) << "Day of Birth" << endl;

	string feature;
	getline(ff, feature);
	matrix_class.push_back(feature);
	int cnt = 0;
	for (string studentID : listOfStudent) {
		Student student;
		student.SetStudentID(studentID);
		student.Reload();
		ff << left << setw(5) << ++cnt
			<< left << setw(15) << student.getStudentID()
			<< left << setw(30) << student.getLastname()
			<< left << setw(10) << student.getFirstname()
			<< left << setw(10) << student.getGender()
			<< left << setw(15) << student.getDoB() << endl;
		getline(ff, feature);
		matrix_class.push_back(feature);
	}
	matrix_class.push_back("RETURN");
	menu studentList(title, matrix_class, 2);

	string result = menu_choose(studentList);
	cnt = 0;
	for (string studentID : listOfStudent) {
		Student student;
		student.SetStudentID(studentID);
		student.Reload();
		ff << left << setw(5) << ++cnt
			<< left << setw(15) << student.getStudentID()
			<< left << setw(30) << student.getLastname()
			<< left << setw(10) << student.getFirstname()
			<< left << setw(10) << student.getGender()
			<< left << setw(15) << student.getDoB() << endl;
		getline(ff, feature);
		if (feature == result) return studentID;
	}
	return "RETURN";
}

void Course::CreateAttendanceList(string link)
{
	AttendanceList attendanceList;

	for (auto i : listOfStudent)
	{
		Attendance attendance;
		attendance.SetStudentID(i);
		attendanceList.Add(attendance);
	}
	attendanceList.SaveData(link + ID + "-attendancelist.txt");
}

string Course::GetClass()
{
	return Class;
}

string Course::GetStudentID(int & pos)
{
	if (pos >= 0 && pos < listOfStudent.size()) return listOfStudent[pos];
	return "";
}

string Course::GetName()
{
	return name;
}

string Course::GetLecturer()
{
	return lecturer;
}

string Course::GetDOW()
{
	return dayOfWeek;
}

string Course::GetStartDate()
{
	return startDate;
}

string Course::GetEndDate()
{
	return endDate;
}

string Course::GetStartHour()
{
	return startHour;
}

string Course::GetEndHour() {
	return endHour;
}

string Course::GetRoom() {
	return room;
}

vector<string> Course::GetStudentList()
{
	return listOfStudent;
}

bool Course::HaveStudent(string StudentID)
{
	for (auto i : listOfStudent) if (i == StudentID) return true;
	return false;
}

void Course::RemoveStudent(string StudentID)
{
	int pos = 0;
	for (string id : listOfStudent) if (id == StudentID) {
		break;
	}
	else ++pos;
	if (pos < 0 || pos >= listOfStudent.size()) return;
	swap(listOfStudent[pos], listOfStudent.back());
	listOfStudent.pop_back();
}

void Course::Reload()
{
	listOfStudent.clear();
	ifstream in("Data\\Course\\" + year + "\\" + semester + "\\" + ID + ".txt");
	getline(in, ID);
	getline(in, name);
	getline(in, Class);
	getline(in, lecturer);
	getline(in, startDate);
	getline(in, endDate);
	getline(in, dayOfWeek);
	getline(in, startHour);
	getline(in, endHour);
	getline(in, room);
	string x;
	while (in >> x) listOfStudent.push_back(x);
	in.close();
}

Course::Course(string& year, string& sem, string & a, string & b, string & c, string & d, string & e, string & f, string & g, string & h, string & i, string & j) :
	year(year), semester(sem), ID(a), name(b), Class(c), lecturer(d), startDate(e), endDate(f), dayOfWeek(g), startHour(h), endHour(i), room(j) {}

Course::Course()
{
	
}

Course::Course(string ID):ID(ID)
{
	ifstream in("Data\\Course\\" + ID + ".txt");
	Reload(in);
}

Course::Course(string year, string sem, string courseID):year(year), semester(sem), ID(courseID)
{
	Reload();
}

void Course::SetYear(string& newYear)
{
	year = newYear;
}

void Course::SetSemester(string& newSemester) {
	semester = newSemester;
}

Attendance::Attendance()
{
	for (int i = 1; i <= 10; ++i) day.push_back(0);
}

void Attendance::SetStudentID(string ID)
{
	StudentID = ID;
}

void Attendance::SaveData(ostream & ou)
{
	ou << StudentID << ' ';
	for (auto i : day) ou << i << ' ';
	ou << '\n';
}

void Attendance::ReloadDay(istream & in)
{
	for (unsigned int i = 0; i < day.size(); ++i) in >> day[i];
}

bool Attendance::CompareStudentID(string ID)
{
	if (ID == StudentID) return true;
	return false;
}

string Attendance::GetStudentID()
{
	return StudentID;
}

vector<int> Attendance::GetAttend()
{
	return day;
}

void Attendance::UpdateAttend(vector<int>& newDay)
{
	day.clear();
	day = newDay;
}

void AttendanceList::EditAttend(Student & student) {
	string studentID = student.getStudentID();
	vector<int> attend = GetAttend(studentID);
	vector<string> attendStatus;
	for (int i = 0; i < (int)attend.size(); ++i) {

		attendStatus.push_back("Week " + to_string(i + 1) + ": ");
	}
	vector<string> answer;
	for (int i = 0; i < (int)attend.size(); ++i) {
		answer.push_back((attend[i] == 0 ? "It's not show time" : (attend[i] == 1 ? "Attend" : "Absent")));
	}
	vector<string> chooselist = { "It's not show time", "Attend", "Absent" };
	attendStatus.push_back("Apply");
	attendStatus.push_back("RETURN");
	menu menuAttendStatus("ATTENDANCE OF " + student.getLastname() + ' ' + student.getFirstname() + " - " + studentID, attendStatus, 1);
	menuAttendStatus.maxLengthInfo = 30;
	if (fill_menu_attend(menuAttendStatus, answer, chooselist)) {
		for (int i = 0; i < (int)attend.size(); ++i) {
			attend[i] = (answer[i] == "It's not show time") ? 0 : ((answer[i] == "Attend") ? 1 : 2);
		}

		UpdateAttend(attend, studentID);
	}
}

void AttendanceList::Add(Attendance attendance)
{
	attend.push_back(attendance);
}

void AttendanceList::Remove(string ID)
{
	for (unsigned int i = 0; i < attend.size(); ++i) if (attend[i].CompareStudentID(ID))
	{
		swap(attend[i], attend.back());
		attend.pop_back();
		break;
	}
}

void AttendanceList::AddStudent(Student & x)
{
	Attendance tmp;
	tmp.SetStudentID(x.getStudentID());
	attend.push_back(tmp);
}

void AttendanceList::SaveData(string link)
{
	ofstream ou(link);
	for (auto i : attend) i.SaveData(ou);
	ou.close();
}

void AttendanceList::Reload(string link)
{
	attend.clear();
	ifstream in(link);
	string x;
	while (in >> x)
	{
		Attendance tmp;
		tmp.SetStudentID(x);
		tmp.ReloadDay(in);
		attend.push_back(tmp);
	}
	in.close();
}

void AttendanceList::ExportAttend(string name)
{
	vector<string> Col = { "Student ID","1","2","3","4","5","6","7","8","9","10" };
	vector<string> Row;
	vector<vector<int>> a;
	vector<int> tmp(10);
	for (auto i : attend)
	{
		Row.push_back(i.GetStudentID());
		a.push_back(tmp);
		a.back() = i.GetAttend();
	}
	Export(Row, Col, name + "-attendancelist", a);
}

vector<int> AttendanceList::GetAttend(string & ID)
{
	for (auto i : attend) if (i.CompareStudentID(ID)) return i.GetAttend();
}

void AttendanceList::UpdateAttend(vector<int>& a, string & ID)
{
	for (unsigned int i = 0; i < attend.size(); ++i) if (attend[i].CompareStudentID(ID))
	{
		attend[i].UpdateAttend(a);
		break;
	}
}

void AttendanceList::View()
{
	vector<string> attendance_matrix;
	stringstream ff;

	ff << left << setw(5) << "No"
		<< left << setw(15) << "Student ID"
		<< left << setw(30) << "Name";
	for (int i = 1; i <= 10; ++i) {
		ff << left << setw(7) << "Week " + to_string(i);
	}
	ff << endl;

	string feature;
	getline(ff, feature);
	attendance_matrix.push_back(feature);
	int cnt = 0;
	for (Attendance att_student : attend) {
		vector<int> att_result = att_student.GetAttend();
		Student student;
		student.SetStudentID(att_student.GetStudentID());
		student.Reload();
		ff << left << setw(5) << ++cnt
			<< left << setw(15) << student.getStudentID()
			<< left << setw(32) << student.getLastname() + ' ' + student.getFirstname();
		for (int i = 1; i <= 10; ++i) {
			char icon = (att_result[i - 1] == 0 ? '-' : (att_result[i - 1] == 1 ? 'X' : 'A'));
			ff << left << setw(7) << icon;
		}
		ff << endl;
		getline(ff, feature);
		attendance_matrix.push_back(feature);
	}
	attendance_matrix.push_back("RETURN");
	menu att_menu("ATTENDANCE LIST", attendance_matrix, 2);
	while (menu_choose(att_menu) != "RETURN");
}

void Scoreboard::ImportScoreboard(string & year, string & sem, string & course, string & name)
{
	Import(name, "Data\\Course\\" + year + "\\" + sem + "\\");

	while (name.back() != '.') name.pop_back();
	name += "txt";

	Course courseTmp;
	courseTmp.SetYear(year);
	courseTmp.SetSemester(sem);
	courseTmp.SetID(course);
	courseTmp.Reload();

	vector<string> listOfStudent = courseTmp.GetStudentList();

	Scoreboard scoreboard;
	scoreboard.Reload("Data\\Course\\" + year + "\\" + sem + "\\" + name);
	scoreboard.CleanUp(listOfStudent);
	scoreboard.Save("Data\\Course\\" + year + "\\" + sem + "\\" + name);

	string command = "Data\\Course\\" + year + "\\" + sem + "\\" + course + "-scoreboard.txt";
	DeleteFile(command.c_str()); // This is to delete the old scoreboard file

	command = "rename Data\\Course\\" + year + "\\" + sem + "\\" + name + " " + course + "-scoreboard.txt";
	system(command.c_str());
}

bool Scoreboard::ExportScoreboard(string & year, string & sem, string & course)
{
	ifstream in("Data\\Course\\" + year + "\\" + sem + "\\" + course + "-scoreboard.txt");
	if (in.fail()) return false;

	vector<string> Col = { "Student ID","Midterm","Practice","Final" };
	vector<int> tmp(3);

	string x;
	int n = 0;
	while (in >> x)
	{
		StudentID.push_back(x);
		scoreboard.push_back(tmp);
		for (int i = 0; i < 3; ++i) in >> scoreboard[n][i];
		n++;
	}
	Export(StudentID, Col, course + "-scoreboard", scoreboard);
}

vector<int> Scoreboard::GetScore(string & student)
{
	for (unsigned int i = 0; i < StudentID.size(); ++i)
		if (StudentID[i] == student) return scoreboard[i];
	vector<int> tmp;
	return tmp;
}

void Scoreboard::UpdateScore(string & student, vector<int>& newScore)
{
	for (unsigned int i = 0; i < StudentID.size(); ++i) if (StudentID[i] == student)
	{
		scoreboard[i] = newScore;
		return;
	}
}

void Scoreboard::CleanUp(vector<string> listOfStudent)
{
	unsigned int i = 0;
	while (i < StudentID.size()) 
	{
		bool found = false;
		for (auto j : listOfStudent)
		{
			if (StudentID[i] == j)
			{
				found = true;
				break;
			}
		}
		if (!found)
		{
			swap(StudentID[i], StudentID.back());
			StudentID.pop_back();
			swap(scoreboard[i], scoreboard.back());
			scoreboard.pop_back();
		}
		else ++i;
	}
}

bool Scoreboard::Reload(string link)
{
	StudentID.clear();
	scoreboard.clear();
	ifstream in(link);
	if (!in.is_open()) return false;

	string tmp;
	vector<int> tmpp(3, 0);
	while (getline(in, tmp))
	{
		StudentID.push_back(tmp);
		scoreboard.push_back(tmpp);
		for (int i = 0; i < 3; ++i)
		{
			getline(in, tmp);
			stringstream ss(tmp);
			ss >> scoreboard.back()[i];
		}
	}
	in.close();
}

void Scoreboard::Save(string link)
{
	ofstream ou(link);
	for (unsigned int i = 0; i < StudentID.size(); ++i)
	{
		ou << StudentID[i] << '\n';
		for (unsigned int j = 0; j < scoreboard[i].size(); ++j) ou << scoreboard[i][j] << '\n';
	}
	ou.close();
}

void Scoreboard::View(string course)
{
	menu board;
	board.minchosen = 2;
	board.chosen = 2;
	board.title = "SCOREBOARD OF COURSE " + course;
	stringstream ff;
	ff  << left << setw(5) << "No"
		<< left << setw(15) << "Student ID"
		<< left << setw(10) << "Midterm"
		<< left << setw(10) << "Practice"
		<< left << setw(10) << "Final" << "\n";
	string feature;
	getline(ff, feature);
	board.name.clear();
	board.name.push_back(feature);
	for (int i = 0; i < StudentID.size(); ++i) {
		ff << left << setw(5) << i + 1
			<< left << setw(15) << StudentID[i]
			<< left << setw(10) << scoreboard[i][0]
			<< left << setw(10) << scoreboard[i][1]
			<< left << setw(10) << scoreboard[i][2] << "\n";
			getline(ff, feature);
			board.name.push_back(feature);
	}
	board.name.push_back("RETURN");
	while (1) {
		string tmp = menu_choose(board);
		if (tmp == "RETURN") return;
	}
}

void Scoreboard::EditGrade(Student & student) {
	menu Menu;
	Menu.title = "EDIT GRADE - " + student.getFirstname() + ' ' + student.getLastname() + " - " + student.getStudentID();
	Menu.name.clear();
	Menu.name = { "Midterm: ",
				"Practice: ",
				"Final: ",
				"Apply",
				"Cancel"
	};
	Menu.minchosen = 1;
	Menu.chosen = 1;
	Menu.maxLengthInfo = 10;
	vector<string> answer;
	string studentID = student.getStudentID();
	vector<int> score = GetScore(studentID);
	answer.clear();
	for (int i = 0; i < 3; ++i)
		answer.push_back(to_string(score[i]));
	
	while (fill_menu(Menu, answer)) {
		for (int i = 0; i < 3; ++i) {
			score[i] = atof(answer[i].c_str());
			if (to_string(score[i]) != answer[i]) {
				// Check if convert unsuccessfully
				Message("Something wrong here.");
				continue;
			}
		}
		UpdateScore(studentID, score);
		return;
	}
}
void CleanUp(Scoreboard a, Course tmp)
{
}
