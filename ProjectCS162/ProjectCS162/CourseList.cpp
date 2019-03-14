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
