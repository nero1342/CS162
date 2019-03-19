#ifndef Student_hpp
#define Student_hpp

#include <iostream>
#include "STL.hpp"

using namespace std;

class Student {
private:
    // Profile
    string StudentID, Lastname, Firstname, Gender, DoB;
    //
    string Class;
	//
	vector<string> Course;
public:

	void Reload();
	void SaveData();

    void ReadData(ifstream &fin, string Class);
	void Edit(Student newProfile);
    
    void SetStudentID(string newStudentID);
    void SetLastname(string newLastname);
    void SetFirstname(string newFirstname);
    void SetGender(string newGender);
    void SetDoB(string newDoB);
    void SetClass(string newClass);

	void AddCourse(string course);

    string getStudentID();
    string getLastname();
    string getFirstname();
    string getGender();
    string getDoB();
    string getClass();
};

#endif /* Student_hpp */
