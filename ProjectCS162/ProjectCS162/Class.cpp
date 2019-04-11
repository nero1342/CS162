#include "Class.hpp"
#include "menu.h"
#include "control.h"
#include <sstream>

void Class::SetName(string newName) {
    name = newName;
}

string Class::GetName() {
	return name;
}

void Class::Import() {
	list.clear();
    std::ifstream fin("Data\\Class\\" + name + ".txt");
	if (!fin.is_open()) return;
	string stt;
	while (fin >> stt) {
		getline(fin, stt);
		Student student;
        student.ReadData(fin, name);
		Add(student);
	}
}
void Class::Reload()
{
	list.clear();
	std::ifstream fin("Data\\Class\\" + name + ".txt");
	if (!fin.is_open()) return;
	string ID;
	while (fin >> ID) {
		Student student;
		student.SetStudentID(ID);
		student.Reload();
		Add(student);
	}
}

void Class::Add(Student student) {
	student.SaveData();
	list.push_back(student);
}

void Class::Remove(Student student) {
	DeleteFile(("Data\\Student\\" + student.getStudentID() + ".txt").c_str());
	for (int i = 0; i < list.size(); ++i) if (list[i].getStudentID() == student.getStudentID())
	{
		swap(list[i], list.back());
		list.pop_back();
		break;
	}
}

string Class::ViewList() {
	string title = "STUDENT LIST OF " + name;
	vector<string> matrix_class;
	Reload();
	stringstream ff;

	ff  << left << setw(5) << "No"
		<< left << setw(15) << "Student ID"
		<< left << setw(30) << "Lastname"
		<< left << setw(10) << "Firstname"
		<< left << setw(10) << "Gender"
		<< left << setw(15) << "Day of Birth" << endl;

	string feature;
	getline(ff, feature);
	matrix_class.push_back(feature);
	int cnt = 0;
	for (Student student : list) {
		student.Reload();
		ff << left << setw(5) << ++cnt
			<< left << setw(15) << student.getStudentID()
			<< left << setw(30) << student.getLastname()
			<< left << setw(10) << student.getFirstname()
			<< left << setw(10) << student.getGender()
			<< left << setw(15) << student.getDoB() << endl;
		getline(ff, feature);
		matrix_class.push_back(feature);
	}
	matrix_class.push_back("RETURN");
	menu studentList(title, matrix_class, 2);

	string result = menu_choose(studentList);
	cnt = 0;
	for (Student student : list) {
		student.Reload();
		ff << left << setw(5) << ++cnt
			<< left << setw(15) << student.getStudentID()
			<< left << setw(30) << student.getLastname()
			<< left << setw(10) << student.getFirstname()
			<< left << setw(10) << student.getGender()
			<< left << setw(15) << student.getDoB() << endl;
		getline(ff, feature);
		if (feature == result) return student.getStudentID();
	}
	return "RETURN";
}

void Class::SaveData() {
	ofstream ou("Data\\Class\\" + name + ".txt");
	int cnt = 0;
	for (auto i : list)
	{
		//ou << ++cnt << '\n';
		ou << i.getStudentID() << '\n';
	}
	list.clear();
}