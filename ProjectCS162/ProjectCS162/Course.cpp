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
	getline(in, Lecturer);
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
	ou << Lecturer << "\n";
	ou << startDate << "\n";
	ou << endDate << "\n";
	ou << dayOfWeek << "\n";
	ou << startHour << "\n";
	ou << endHour << "\n";
	ou << room << "\n";
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
		x.Reload();
		x.AddCourse(ID);
		x.SaveData();
	}

	/*
		need to create account for lecturer here
	*/
}
