#pragma once
#ifndef Course_h
#define Course_h

#include "STL.hpp"
#include "Student.hpp"
#include "Lecturer.hpp"
#include "AccountList.hpp"

class Scoreboard
{
private:
	vector<vector<int>> scoreboard;
	vector<string> StudentID;
public:
	void ImportScoreboard(string year, string &sem, string &course, string &name);
	bool ExportScoreboard(string & year, string &sem, string &course);
};

class Attendance
{
private:
	vector<int> day;
	string StudentID;
public:
	Attendance();
	void SetStudentID(string ID);
	void SaveData(ostream & ou);
	void ReloadDay(istream & in);
	bool CompareStudentID(string ID);

	string GetStudentID();
	vector<int> GetAttend();
	void UpdateAttend(vector<int> & a);
};

class AttendanceList
{
private:
	vector<Attendance> attend;
public:
	void Add(Attendance x);
	void Remove(string ID);

	void SaveData(string link);
	void Reload(string link);
	void ExportAttend(string name);
	vector<int> GetAttend(string & ID);
	void UpdateAttend(vector<int> &a, string &ID);
	void View();
};

class Course
{
private:
	string ID, name, Class, lecturer, startDate, endDate, dayOfWeek, startHour, endHour, room;
	vector<string> listOfStudent;
public:
	string GetID();
	string GetClass();
	string GetStudentID(int &pos);

	void RemoveStudent(string StudentID);

	void SetID(string name);
	void Reload(istream & in); 
	void ReadInput(istream & in);  // this is for import only
	void SaveData(ofstream & ou);
	void Import();
	void CreateAccountForLecturer(); 
	void DeleteCourse();

	string ViewListStudent();

	void CreateAttendanceList(string link);

	Course(string &, string &, string &, string &, string &, string &, string &, string &, string &, string &);
	Course();
};

#endif
