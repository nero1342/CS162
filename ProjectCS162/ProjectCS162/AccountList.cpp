#include "AccountList.hpp"

Account AccountList::Find(string &username)
{
	for (Account acc : list) if (acc.getUsername() == username) return acc;
}

void AccountList::ChangePass(string username, string newPassword)
{
	for (Account acc : list)
		if (acc.getUsername() == username)
		{
			acc.ChangePassword(newPassword);
			SaveData();
			return;
		}
}

bool AccountList::isExist(string username) {
    for (Account acc : list) if (acc.getUsername() == username) {
        return true;
    }
    return false;
}

void AccountList::Add(Student student) {
    if (isExist(student.getStudentID())) return;
	student.SaveData();
    list.push_back(Account(student.getStudentID(), student.getDoB(), "Student", student.getClass()));
}

void AccountList::Edit(Student student) {
    for (Account &acc : list) {
        if (acc.getUsername() == student.getStudentID()) {
            acc.EditLink(student.getClass());
            return;
        }
    }
}

void AccountList::Add(Lecturer lecturer) {
    if (isExist(lecturer.getName())) return;
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

void AccountList::Add(Account account)
{
	if (isExist(account.getUsername())) return;
	list.push_back(account);
}

void AccountList::Reload() {
    list.clear();
    ifstream cin("Data\\Account.txt");
	if (!cin.is_open()) return;
    int n;
    string username, password, type, link;
    while (cin >> n) {
        cin >> username >> password >> type >> link;
        list.push_back(Account(username, password, type, link));
    }
    cin.close();
}

void AccountList::SaveData() {
    ofstream cout("Data\\Account.txt");
    int n = 0;
    for (Account acc : list) {
        ++n;
        cout << n << endl;
        cout << acc.getUsername() << endl;
        cout << acc.getPassword() << endl;
        cout << acc.getType() << endl;
        cout << acc.getLink() << endl;
    }
	list.clear();
	cout.close();
}

void AccountList::ImportClass(string Class) {
	Reload();
	Import(Class,"Data\\Class\\");
	while (Class.back() != '.') Class.pop_back();
    Class.pop_back();
	std::ifstream fin("Data\\Class\\" + Class + ".txt");
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
