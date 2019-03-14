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
	ifstream in("Data\\Course\\" + ID + ".txt");
	if (!in.is_open()) {
		return;
	}
	in >> name >> Class >> startDate >> endDate >> dayOfWeek >> startHour >> endHour >> room;
	in.close();
}
