#include "AccountList.hpp"
#include "Importer.h"

bool AccountList::isExist(string username) {
    for (Account acc : list) if (acc.getUsername() == username) {
        return true;
    }
    return false;
}

void AccountList::Add(Student student) {
    list.push_back(Account(student.getStudentID(), student.getDoB(), "Student", student.getClass()));
}

void AccountList::Add(Lecturer lecturer) {
    list.push_back(Account(lecturer.getName(), lecturer.getName(), "Lecturer", "Lecturer"));
}

bool AccountList::Login(string username, string password) {
    for (Account acc : list) if (acc.Login(username, password)) {
        return true;
    }
    return false;
}

void AccountList::Remove(string username) {
    int i = 0;
    for (Account acc : list) if (acc.getUsername() == username) {
        list.erase(list.begin() + i);
        SaveData();
        return;
    } else ++i;
}

void AccountList::LoadData() {
    list.clear();
    ifstream cin("Account.txt");
    int n;
    string username, password, type, link;
    while (cin >> n) {
        cin >> username >> password >> type >> link;
        list.push_back(Account(username, password, type, link));
    }
    cin.close();
}

void AccountList::SaveData() {
    ofstream cout("Account.txt");
    int n = 0;
    for (Account acc : list) {
        ++n;
        cout << n << endl;
        cout << acc.getUsername() << endl;
        cout << acc.getPassword() << endl;
        cout << acc.getType() << endl;
        cout << acc.getLink() << endl;
    }
    cout.close();
}

void AccountList::ImportClass(string Class) {
    Import(Class);
	while (Class.back() != '.') Class.pop_back();
    Class.pop_back();
	std::ifstream fin(Class + ".txt");
	string stt;
	while (getline(fin, stt)) {
		Student student;
        student.ReadData(fin, Class);
        if (!isExist(student.getStudentID())) {
            Add(student);
        }
	}
    SaveData();
}
