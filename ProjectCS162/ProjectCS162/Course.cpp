#include "Course.h"
#include <sstream>
#include <iomanip>
#include "menu.h"
#include "control.h"

string Course::GetID()
{
	return ID;
}

void Course::SetID(string name)
{
	ID = name;
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
		x.AddCourse(ID);
		x.SaveData();
	}

	CreateAccountForLecturer();
}

void Course::CreateAccountForLecturer()
{
	Lecturer lect(lecturer);
	AccountList acclist;
	acclist.Reload();
	acclist.Add(lect);
	acclist.SaveData();
}

void Course::DeleteCourse()
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
		x.Reload();
		x.RemoveCourse(ID);
		x.SaveData();
	}
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
Course::Course(string & a, string & b, string & c, string & d, string & e, string & f, string & g, string & h, string & i, string & j) :
	ID(a), name(b), Class(c), lecturer(d), startDate(e), endDate(f), dayOfWeek(g), startHour(h), endHour(i), room(j) {}

Course::Course()
{
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

void AttendanceList::Add(Attendance x)
{
	attend.push_back(x);
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
	}
	in.close();
}
