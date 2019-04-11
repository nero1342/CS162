#include "Lecturer.hpp"
#include "menu.h"
#include "control.h"
#include <sstream>
#include "Course.h"

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
	course.clear();
	while (getline(cin, courseID)) {
		course.push_back(courseID);
	}
	cin.close();
}

void Lecturer::SaveData()
{
	ofstream cout("Data\\Lecturer\\" + Name + ".txt");
	for (string courseID : course) {
		cout << courseID << endl;
	}
	cout.close();
}

vector<string>& Lecturer::getListCourse() {
	return course;
}

void Lecturer::AddCourse(string CourseID) {
	Reload();
	for (auto i : course) if (i == CourseID) return;
	course.push_back(CourseID);
	SaveData();
}

void Lecturer::DeleteCourse(string CourseID) {
	Reload();
	int cnt = 0;
	for (string id : course) {
		if (id == CourseID) {
			course.erase(course.begin() + cnt);
			break;
		}
		++cnt;
	}
	SaveData();
}

string Lecturer::ViewCourse()
{
	//vector<string> myCourse = course;
	//myCourse.push_back("RETURN");
	//menu courseMenu("COURSES OF " + Name, myCourse, 1);
	//return menu_choose(courseMenu);
	string title = "COURSE LIST OF " + Name;
	vector<string> schedule;
	stringstream ff;
	ff << left << setw(5) << "No"
		<< left << setw(30) << "Course ID"
		<< left << setw(30) << "Course Name"
		<< left << setw(10) << "DOW"
		<< left << setw(12) << "Start Hour"
		<< left << setw(12) << "End Hour"
		<< left << setw(10) << "Room" << endl;

	string feature;
	getline(ff, feature);
	schedule.push_back(feature);
	int cnt = 0;
	for (string courseID : course) {
		Course myCourse(courseID);
		ff << left << setw(5) << ++cnt
			<< left << setw(30) << courseID
			<< left << setw(30) << myCourse.GetName()
			<< left << setw(10) << myCourse.GetDOW()
			<< left << setw(12) << myCourse.GetStartHour()
			<< left << setw(12) << myCourse.GetEndHour()
			<< left << setw(10) << myCourse.GetRoom() << endl;
		getline(ff, feature);
		schedule.push_back(feature);
	}
	schedule.push_back("RETURN");
	menu schedule_menu(title, schedule, 2);

	while (true) {
		string result = menu_choose(schedule_menu);
		if (result == "RETURN") return result;
		ff << result;
		int no;
		ff >> no;
		return course[no - 1];
	}
}
