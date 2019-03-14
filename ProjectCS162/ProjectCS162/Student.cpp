#include "Student.hpp"

void Student::ReadData(ifstream &fin, string Class) {
    this -> Class = Class;
    getline(fin, StudentID);
    getline(fin, Firstname);
    getline(fin, Lastname);
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