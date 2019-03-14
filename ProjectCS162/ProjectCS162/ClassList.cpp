#include "ClassList.hpp"

void ClassList::AddClass(string nameClass) {
    // Remove tail .csv
    while (nameClass.back() != '.') nameClass.pop_back();
    nameClass.pop_back();
    //
	Class newClass;
    newClass.SetName(nameClass);
    newClass.Reload();
    listClass[nameClass] = newClass;
    SaveData();
}

void ClassList::AddStudent(Student student) {
    Class &myClass = listClass[student.getClass()];
    myClass.Add(student);
    myClass.SaveData();
}

void ClassList::RemoveStudent(Student student) {
    Class &myClass = listClass[student.getClass()];
    myClass.Remove(student);
    myClass.SaveData();
}

void ClassList::Reload() {
    listClass.clear();
    ifstream cin("Data\\ClassList.txt");
	if (!cin.is_open()) return;
    string nameClass;
    while (cin >> nameClass) {
        Class newClass;
        newClass.SetName(nameClass);
        // Reload when we need or reload all at beginning??
        newClass.Reload();
        listClass[nameClass] = newClass;
    }
    cin.close();
}

void ClassList::SaveData() {
    ofstream cout("Data\\Class\\ClassList.txt");
    for (auto nameClass : listClass) {
        cout << nameClass.first << endl;
    }
    cout.close();
}

void ClassList::ViewList() {

}