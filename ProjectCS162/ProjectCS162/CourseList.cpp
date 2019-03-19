#include "CourseList.h"

void CourseList::ImportCourse(string & year, string &sem, string & name)
{
	year = "Data\\Course\\" + year + "\\" + sem + "\\";
	Import(name, year);
	
	while (name.back() != '.') name.pop_back();
	name += "txt";
	ifstream in(year + name);
	string No;
	vector<Course> course;
	while (getline(in, No))
	{
		Course tmp;
		tmp.ReadInput(in);

		course.push_back(tmp);
	}
	in.close();

	string link = year + name;
	DeleteFile(link.c_str());

	ofstream ou(year + "CourseList.txt");
	for (auto i : course) ou << i.GetID() << '\n';
	ou.close();

	for (auto i : course)
	{
		ou.open(year + i.GetID() + ".txt");
		i.SaveData(ou);
		ou.close();
	}
	for (auto i : course) i.Import();
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

