#include "Class.hpp"

void Class::SetName(string newName) {
    name = newName;
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

void Class::ViewList() {

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