#ifndef Student_hpp
#define Student_hpp

#include <iostream>

using namespace std;

class Student {
private:
    // Profile
    string StudentID, Lastname, Firstname, Gender, DoB;
    //
    string Class;
public:

    void ReadData(ifstream &fin, string Class);
    void Edit(Student newProfile);
    string getStudentID();
    string getLastname();
    string getFirstname();
    string getGender();
    string getDoB();
    string getClass();
};

#endif /* Student_hpp */
