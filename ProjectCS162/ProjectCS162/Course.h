#pragma once
#ifndef Course_h
#define Course_h

#include "STL.hpp"
#include "Student.hpp"
#include "Lecturer.hpp"
#include "AccountList.hpp"

class Course
{
private:
	string ID, name, Class, lecturer, startDate, endDate, dayOfWeek, startHour, endHour, room;
<<<<<<< HEAD
=======
	vector<string> listOfStudent;
>>>>>>> 814f40f6dc54fbf5b2bf08819879e15bb1244639
public:
	string GetID();
	string GetClass();
	string GetStudentID(int &pos);

	void RemoveStudent(int &pos);

	void SetID(string name);
	void ReadInput(istream & in); 
	void SaveData(ofstream & ou);
	void Import();
	void CreateAccountForLecturer(); 
	/*
		need to add create account here
	*/
	void DeleteCourse();

	Course(string &, string &, string &, string &, string &, string &, string &, string &, string &, string &);
	Course();
};

#endif
