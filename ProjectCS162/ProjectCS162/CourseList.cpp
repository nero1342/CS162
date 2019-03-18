#include "CourseList.h"

void CourseList::AddCourse(Course x)
{
	courseList.push_back(x);
}

void CourseList::RemoveCourse(Course x)
{
	for (auto i : courseList) if (i.GetID() == x.GetID())
	{
		string tmp = "Data\\Course\\" + i.GetID();
		DeleteFile(tmp.c_str());
		swap(i, courseList.back());
		courseList.pop_back();
		break;
	}
	SaveData();
	Reload();
}

void CourseList::CreateAcademicYear(string name)
{
#define SaveLocation "Data\\AcademicYear.txt"

	vector<string> year;
	ifstream in(SaveLocation);
	string x;
	while (in >> x)
	{
		if (x == name)
		{
			in.close();
			return;
		}
		year.push_back(x);
	}
	in.close();

	ofstream ou(SaveLocation);
	for (auto i : year) ou << i << '\n';
	ou << name;
	ou.close();

	name = "md Data\\Course\\" + name;
	system(name.c_str());
}

void CourseList::Reload()
{
	courseList.clear();
	ifstream in("Data\\Course\\CourseList.txt");
	string name;
	while (in >> name)
	{
		Course tmp;
		tmp.SetID(name);
		tmp.Reload();
		courseList.push_back(tmp);
	}
	in.close();
}

void CourseList::SaveData()
{
	ofstream ou("Data\\Course\\CourseList.txt");
	for (auto i : courseList) ou << i.GetID() << '\n';
}

bool CourseList::isExisted(Course x)
{
	for (auto i : courseList) if (i.GetID() == x.GetID()) return true;
	return false;
}
