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

void CourseList::CreateAcademicYear(string &name)
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

void CourseList::CreateSemester(string & name, string & sem)
{
	name = "Data\\Course\\" + name;
	vector<string> sems;
	string link = name + "\\Semester.txt";

	ifstream in(link);
	string x;
	while (in >> x)
	{
		if (x == sem)
		{
			in.close();
			return;
		}
		sems.push_back(x);
	}
	in.close();

	ofstream ou(link);
	for (auto i : sems) ou << i << '\n';
	ou << sem << '\n';
	ou.close();

	name = "md " + name + "\\" + sem;
	system(name.c_str());
}

void CourseList::DeleteAcademicYear(string & name)
{
	string link = "Data\\AcademicYear.txt";
	vector<string> year;
	string x;

	ifstream in(link);
	while (in >> x) year.push_back(x);
	in.close();

	for (int i = 0; i < year.size(); ++i) if (year[i] == name)
	{
		swap(year[i], year.back());
		year.pop_back();
	}

	ofstream ou(link);
	for (auto i : year) ou << i << '\n';
	ou.close();

	name = "rmdir /s /q Data\\Course\\" + name;
	system(name.c_str());
}

void CourseList::DeleteSemester(string & name, string &sem)
{
	name = "Data\\Course\\" + name;
	vector<string> sems;
	string link = name + "\\Semester.txt";
	string x;

	ifstream in(link);
	while (in >> x) sems.push_back(x);
	in.close();

	for (int i = 0; i < sems.size(); ++i) if (sems[i] == sem)
	{
		swap(sems[i], sems.back());
		sems.pop_back();
	}

	ofstream ou(link);
	for (auto i : sems) ou << i << '\n';
	ou.close();

	name = "rmdir /s /q " + name + "\\" + sem;
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
