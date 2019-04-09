#ifndef Lecturer_hpp
#define Lecturer_hpp

#include <iostream>
#include "STL.hpp"

using namespace std;

class Lecturer {
private:
    string Name;
	vector<string> Course;

public:
	Lecturer();
	Lecturer(string Name);
	string getName(); 

	void Reload();
	void SaveData();
	vector<string> &getListCourse();
	void AddCourse(string CourseID);

	void DeleteCourse(string CourseID);
	string ViewCourse();
};

#endif /* Lecturer_hpp */
