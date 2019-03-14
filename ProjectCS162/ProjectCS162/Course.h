#pragma once
#ifndef Course_h
#define Course_h

#include "STL.hpp"

class Course
{
private:
	string ID, name, Class, startDate, endDate, dayOfWeek, startHour, endHour, room;
public:
	string GetID();

	void SetID(string name);
	void Reload();
};

#endif
