#include "Course.h"

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

void Course::RemoveStudent(int & pos)
{
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
