#include "Class.hpp"

void Class::SetName(string newName) {
    name = newName;
}

void Class::Reload() {
    std::ifstream fin(name + ".txt");
	string stt;
	while (getline(fin, stt)) {
		Student student;
        student.ReadData(fin, name);
        Add(student);
	}
} 

void Class::Add(Student student) {

}

void Class::Remove(Student student) {

}

void Class::ViewList() {

}

void Class::SaveData() {
    
}