#pragma once
#ifndef CourseList_h
#define CourseList_h

#include "Course.h"

class CourseList
{
private:
	vector<string> courseList;
public:
	void ImportCourse(string &year, string &sem, string &name);
	void AddCourse(string &year, string &sem, Course &a);

	void CreateAcademicYear(string &name);
	void CreateSemester(string &name, string &sem);
	void DeleteAcademicYear(string &name);
	void DeleteSemester(string &name, string &sem);
};

#endif
