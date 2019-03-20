#include "Student.hpp"

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
	Course.clear();
	while (getline(cin, courseID)) {
		Course.push_back(courseID);
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
	for (string courseID : Course) {
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

void Student::AddCourse(string course)
{
	for (auto i : Course) if (i == course) return;
	Course.push_back(course);
}

void Student::RemoveCourse(string & course)
{
	for (unsigned int i = 0; i < Course.size(); ++i) if (Course[i] == course)
	{
		swap(Course[i], Course.back());
		Course.pop_back();
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