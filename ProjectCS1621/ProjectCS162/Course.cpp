#include "Course.h"

string Course::GetID()
{
	return ID;
}

void Course::SetID(string name)
{
	ID = name;
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
	string x;
	while (in >> x) listOfStudent.push_back(x);
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
