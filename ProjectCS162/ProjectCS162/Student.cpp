#include "Student.hpp"
#include "menu.h"
#include "control.h"
#include <sstream>
#include "Course.h"

Student::Student()
{
}

Student::Student(string StudentID):StudentID(StudentID)
{
	Reload();
}

void Student::Reload() {
	ifstream cin("Data\\Student\\" + StudentID + ".txt");
	if (!cin.is_open()) return;
	getline(cin, StudentID);
	getline(cin, Lastname);
	getline(cin, Firstname);
	getline(cin, Gender);
	getline(cin, DoB);
	getline(cin, Class);
	//Course
	string courseID;
	course.clear();
	while (getline(cin, courseID)) {
		course.push_back(courseID);
	}
	cin.close();
}

void Student::SaveData()
{
	ofstream cout("Data\\Student\\" + StudentID + ".txt");
	cout << StudentID << endl;
	cout << Lastname << endl;
	cout << Firstname << endl;
	cout << Gender << endl;
	cout << DoB << endl;
	cout << Class << endl;
	for (string courseID : course) {
		cout << courseID << endl;
	}
	cout.close();
}

void Student::ReadData(ifstream &fin, string Class) {
    this -> Class = Class;
    getline(fin, StudentID);
    getline(fin, Lastname);
    getline(fin, Firstname);
    getline(fin, Gender);
    getline(fin, DoB);
}

void Student::Edit(Student newProfile) {
    *this = newProfile;
}

void Student::SetStudentID(string newStudentID) {
    StudentID = newStudentID;
}

void Student::SetLastname(string newLastname) {
    Lastname = newLastname;
}

void Student::SetFirstname(string newFirstname) {
    Firstname = newFirstname;
}

void Student::SetGender(string newGender) {
    Gender = newGender;
}

void Student::SetDoB(string newDoB) {
    DoB = newDoB;
}

void Student::SetClass(string newClass) {
    Class = newClass;
}

void Student::AddCourse(string courseID)
{
	for (auto i : course) if (i == courseID) return;
	course.push_back(courseID);
}

void Student::RemoveCourse(string & courseID)
{
	for (unsigned int i = 0; i < course.size(); ++i) if (course[i] == courseID)
	{
		swap(course[i], course.back());
		course.pop_back();
		break;
	}
}

string Student::getStudentID() {
    return StudentID;
}

string Student::getFirstname() {
    return Firstname;
}

string Student::getLastname() {
    return Lastname;
}

string Student::getGender() {
    return Gender;
}

string Student::getDoB() {
    return DoB;
}

string Student::getClass() {
    return Class;
}

void Student::ViewSchedule()
{
	string title = "SCHEDULE LIST OF " + Lastname + " " + Firstname + " - " + StudentID;
	vector<string> schedule;
	stringstream ff;

	ff << left << setw(5) << "No"
		<< left << setw(15) << "Course ID"
		<< left << setw(30) << "Course Name"
		<< left << setw(10) << "Class"
		<< left << setw(10) << "Lecturer"
		<< left << setw(10) << "DOW"
		<< left << setw(10) << "Start Hour"
		<< left << setw(10) << "End Hour"
		<< left << setw(10) << "Room" << endl;

	string feature;
	getline(ff, feature);
	schedule.push_back(feature);
	int cnt = 0;
	for (string courseID : course) {
		Course myCourse(courseID);
		ff << left << setw(5) << ++cnt
			<< left << setw(15) << courseID
			<< left << setw(30) << myCourse.GetName()
			<< left << setw(10) << myCourse.GetClass()
			<< left << setw(10) << myCourse.GetLecturer()
			<< left << setw(10) << myCourse.GetDOW()
			<< left << setw(10) << myCourse.GetStartHour()
			<< left << setw(10) << myCourse.GetEndHour()
			<< left << setw(10) << myCourse.GetRoom() << endl;
		getline(ff, feature);
		schedule.push_back(feature);
	}
	schedule.push_back("RETURN");
	menu schedule_menu(title, schedule, 2);

	while (menu_choose(schedule_menu) != "RETURN");
}
