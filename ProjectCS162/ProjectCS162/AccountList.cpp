#include "AccountList.hpp"

bool AccountList::isExist(string username) {
    for (Account acc : list) if (acc.username == username) {
        return true;
    }
    return false;
}

void AccountList::Add(Student student) {
    list.push_back(Account(student.StudentID, student.DoB, "Student", student.Class));
}

void AccountList::Add(Lecturer lecturer) {
    list.push_back(Account(lecturer.Name, lecturer.Name, "Lecturer", "Lecturer"));
}

void AccountList::Remove(string username) {
    int i = 0;
    for (Account acc : list) if (acc.username == username) {
        list.erase(list.begin() + i);
        return;
    } else ++i;
}

