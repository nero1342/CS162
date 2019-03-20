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
public:
	string GetID();

	void SetID(string name);
	void ReadInput(istream & in); 
	void SaveData(ofstream & ou);
	void Import();
	void CreateAccountForLecturer(); 
	/*
		need to add create account here
	*/
	
	Course(string &, string &, string &, string &, string &, string &, string &, string &, string &, string &);
	Course();
};

#endif
