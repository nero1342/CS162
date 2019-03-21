#pragma once
#ifndef CourseList_h
#define CourseList_h

#include "Course.h"

class CourseList
{
private:
	vector<string> courseList;
public:
	string GetCourse(int pos);

	void Load(string &year, string &sem);
	void Save(string &year, string &sem);

	void ImportCourse(string year, string &sem, string &name);
	void AddCourse(string &year, string &sem, Course &a);
	void RemoveCourse(string year, string &sem, string &name);

	void CreateAcademicYear(string &name);
	void CreateSemester(string &name, string &sem);
	void DeleteAcademicYear(string &name);
	void DeleteSemester(string &name, string &sem);
};

#endif
