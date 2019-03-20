#include "ClassList.hpp"
#include "menu.h"
#include "control.h"

void ClassList::AddClass(string nameClass) {
	Reload();
    // Remove tail .csv
    while (nameClass.back() != '.') nameClass.pop_back();
    nameClass.pop_back();
    //
	// if (isExisted(nameClass)) {}
	Class newClass;
    newClass.SetName(nameClass);
	newClass.Import();
	newClass.SaveData();
	listClass.push_back(nameClass);
    SaveData();
}

void ClassList::AddStudent(Student student) {
	Class myClass;
	myClass.SetName(student.getClass());
	myClass.Reload();
    myClass.Add(student);
    myClass.SaveData();
}

void ClassList::RemoveStudent(Student student) {
	Class myClass;
	myClass.SetName(student.getClass());
	myClass.Reload();
	myClass.Remove(student);
    myClass.SaveData();
}

void ClassList::Reload() {
    listClass.clear();
    ifstream cin("Data\\ClassList.txt");
	if (!cin.is_open()) return;
    string nameClass;
    while (cin >> nameClass) {
        listClass.push_back(nameClass);
    }
    cin.close();
}

void ClassList::SaveData() {
    ofstream cout("Data\\ClassList.txt");
    for (string nameClass : listClass) {
        cout << nameClass << endl;
    }
	listClass.clear();
    cout.close();
}

string ClassList::ViewList() {
	Reload();
	menu classList("LIST OF CLASS", listClass, 1);
	return menu_choose(classList);
}