#include "Class.hpp"

void Class::SetName(string newName) {
    name = newName;
}

void Class::Reload() {
    std::ifstream fin(name + ".txt");
	string stt;
	while (fin >> stt) {
		Student student;
        student.ReadData(fin, name);
        Add(student);
	}
} 

void Class::Add(Student student) {
	list.push_back(student);
}

void Class::Remove(Student student) {
	for (int i = 0; i < list.size(); ++i) if (list[i].getStudentID() == student.getStudentID())
	{
		swap(list[i], list.back());
		list.pop_back();
		break;
	}
}

void Class::ViewList() {

}

void Class::SaveData() {
	ofstream ou(name + ".txt");
	int cnt = 0;
	for (auto i : list)
	{
		ou << ++cnt << '\n';
		ou << i.getStudentID() << '\n';
		ou << i.getLastname() << '\n';
		ou << i.getFirstname() << '\n';
		ou << i.getGender() << '\n';
		ou << i.getDoB() << '\n';
	}
}