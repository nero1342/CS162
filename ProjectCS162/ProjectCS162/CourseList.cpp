#include "CourseList.h"

string CourseList::GetCourse(int pos)
{
	if (pos >= 0 && pos < courseList.size()) return courseList[pos];
	return "";
}

void CourseList::Load(string & year, string & sem)
{
	ifstream in("Data\\Course\\" + year + "\\" + sem + "\\CourseList.txt");
	string x;
	while (in >> x) courseList.push_back(x);
	in.close();
}

void CourseList::Save(string & year, string & sem)
{
	ofstream ou("Data\\Course\\" + year + "\\" + sem + "\\CourseList.txt");
	for (auto i : courseList) ou << i << '\n';
	ou.close();
}

void CourseList::ImportCourse(string year, string &sem, string & name)
{
	string yearsem = "Data\\Course\\" + year + "\\" + sem + "\\";
	Import(name, yearsem);
	
	while (name.back() != '.') name.pop_back();
	name += "txt";
	ifstream in(yearsem + name);
	string No;
	vector<Course> course;
	while (getline(in, No))
	{
		Course tmp;
		tmp.ReadInput(in);

		course.push_back(tmp);
	}
	in.close();

	string link = yearsem + name;
	DeleteFile(link.c_str());

	ofstream ou(yearsem + "CourseList.txt");
	for (auto i : course) ou << i.GetCourseID() << '\n';
	ou.close();

	for (unsigned int i = 0; i < course.size(); ++i)
	{
		course[i].Import();
		course[i].CreateAttendanceList(yearsem);
		course[i].CreateAccountForLecturer(year, sem);
	}
	for (auto i : course)
	{
		ou.open(yearsem + i.GetCourseID() + ".txt");
		i.SaveData(ou);
		ou.close();
	}
}

void CourseList::AddCourse(string &year, string &sem, Course & a)
{
	a.Import();
	ofstream ou("Data\\Course\\" + year + "\\" + sem + "\\" + a.GetCourseID() + ".txt");
	a.SaveData(ou);
	ou.close();
	a.CreateAttendanceList("Data\\Course\\" + year + "\\" + sem + "\\");
	courseList.push_back(a.GetCourseID());
}

void CourseList::RemoveCourse(string year, string & sem, string & name)
{
	Load(year, sem);
	for (unsigned int i = 0; i < courseList.size(); ++i) if (courseList[i] == name)
	{
		swap(courseList[i], courseList.back());
		courseList.pop_back();
		break;
	}
	Save(year, sem);

	year = "Data\\Course\\" + year + "\\" + sem + "\\" + name + ".txt";
	ifstream in(year);
	Course tmp;
	tmp.Reload(in);
	in.close();

	DeleteFile(year.c_str());
	while (!year.empty() && year.back() != '.') year.pop_back();
	year.pop_back();
	year += "-attendancelist.txt";
	DeleteFile(year.c_str());

	while (!year.empty() && year.back() != '-') year.pop_back();
	year.pop_back();
	year += "-scoreboard.txt";
	DeleteFile(year.c_str());

	tmp.DeleteCourse();
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

void CourseList::CreateSemester(string & year, string & sem)
{
	year = "Data\\Course\\" + year;
	vector<string> sems;
	string link = year + "\\Semester.txt";

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

	year = "md " + year + "\\" + sem;
	system(year.c_str());
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

