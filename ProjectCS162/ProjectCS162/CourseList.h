#pragma once
#ifndef CourseList_h
#define CourseList_h

#include "Course.h"

class CourseList
{
private:
	vector<Course> courseList;
public:
	void ImportCourse(string course);
	void AddCourse(Course x);
	void RemoveCourse(Course x); // not done yet

	void Reload();
	void SaveData();

	void ViewList();
	bool isExisted(Course x);
};

#endif