#include "Student.hpp"
#include "Importer.h"

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