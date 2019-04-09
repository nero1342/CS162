#include "Lecturer.hpp"
#include "menu.h"
#include "control.h"

Lecturer::Lecturer()
{
}

Lecturer::Lecturer(string Name):Name(Name)
{
}

string Lecturer::getName() {
    return Name;
}

void Lecturer::Reload()
{
	ifstream cin("Data\\Lecturer\\" + Name + ".txt");
	if (!cin.is_open()) return;
	//Course
	string courseID;
	Course.clear();
	while (getline(cin, courseID)) {
		Course.push_back(courseID);
	}
	cin.close();
}

void Lecturer::SaveData()
{
	ofstream cout("Data\\Lecturer\\" + Name + ".txt");
	for (string courseID : Course) {
		cout << courseID << endl;
	}
	cout.close();
}

vector<string>& Lecturer::getListCourse() {
	return Course;
}

void Lecturer::AddCourse(string CourseID) {
	Reload();
	for (auto i : Course) if (i == CourseID) return;
	Course.push_back(CourseID);
	SaveData();
}

void Lecturer::DeleteCourse(string CourseID) {
	Reload();
	int cnt = 0;
	for (string id : Course) {
		if (id == CourseID) {
			Course.erase(Course.begin() + cnt);
			break;
		}
		++cnt;
	}
	SaveData();
}

string Lecturer::ViewCourse()
{
	vector<string> myCourse = Course;
	myCourse.push_back("RETURN");
	menu courseMenu("COURSES OF " + Name, myCourse, 1);
	return menu_choose(courseMenu);
}
