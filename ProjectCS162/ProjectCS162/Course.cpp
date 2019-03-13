#include "Course.h"

string Course::GetID()
{
	return ID;
}

void Course::SetID(string name)
{
	ID = name;
}

void Course::Reload()
{
	ifstream in(ID + ".txt");
	in >> name >> Class >> startDate >> endDate >> dayOfWeek >> startHour >> endHour >> room;
	in.close();
}
