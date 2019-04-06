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

void Course::Reload(istream & in)
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
	AttendanceList a;

	for (auto i : listOfStudent)
	{
		Attendance tmp;
		tmp.SetStudentID(i);
		a.Add(tmp);
	}
	a.SaveData(link + ID + "-attendancelist.txt");
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

void Attendance::UpdateAttend(vector<int>& a)
{
	day.clear();
	day = a;
}

void AttendanceList::Add(Attendance x)
{
	attend.push_back(x);
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
		ff << left << setw(10) << "Week " + to_string(i);
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
			<< left << setw(30) << student.getLastname() + ' ' + student.getFirstname();
		for (int i = 1; i <= 10; ++i) {
			ff << left << setw(10) << att_result[i - 1];
		}
		ff << endl;
		getline(ff, feature);
		attendance_matrix.push_back(feature);
	}
	attendance_matrix.push_back("RETURN");
	menu att_menu("ATTENDANCE LIST", attendance_matrix, 2);
	while (menu_choose(att_menu) != "RETURN");
}

void Scoreboard::ImportScoreboard(string year, string & sem, string & course, string & name)
{
	Import(name, "Data\\Course\\" + year + "\\" + sem + "\\");

	while (name.back() != '.') name.pop_back();
	name += "txt";

	string tmp = "Data\\Course\\" + year + "\\" + sem + "\\" + course + "-scoreboard.txt";
	year = "rename Data\\Course\\" + year + "\\" + sem + "\\" + name + " " + course + "-scoreboard.txt";
	DeleteFile(tmp.c_str());

	system(year.c_str());
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

bool Scoreboard::Reload(string link)
{
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

void Scoreboard::View()
{
	cout << "liu liu\n";
}
