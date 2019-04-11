#pragma once
#ifndef MENU_H
#define MENU_H

#include<iostream>
#include<string>
#include<vector>
#include"window.h"

using namespace std;

struct menu {
public:
	string title;
	vector<string > name;
	int chosen, minchosen;
	const int begin = 10;
	int maxLengthInfo = 0;

	menu();
	menu(string title, vector<string> &name, int minchosen);
	void Assign(string _title, vector<string>& _name, int _minchosen);
	int maxLength();

	int startPointInfo();
	int endPointInfo();
	int startPointTitle();
};

void staff_menu(menu &now);



class MenuFunction {
public:
	vector<string> STAFF_MENU = { "CLASS",
									"COURSES",
									"SCOREBOARD",
									"ATTENDANCE LIST",
									"VIEW PROFILE INFO",
									"CHANGE PASSWORD",
									"LOGOUT" };

	vector<string> STUDENT_MENU = { "CHECK-IN",
									"VIEW CHECK-IN RESULT",
									"VIEW SCHEDULES",
									"VIEW SCORES OF A COURSE",
									"VIEW PROFILE INFO",
									"CHANGE PASSWORD",
									"LOGOUT" };

	vector<string> LECTURER_MENU = { "VIEW LIST OF COURSES",
									"VIEW ATTENDANCE LIST OF A COURSE",
									"EDIT AN ATTENDANCE",
									"IMPORT SCOREBOARD OF A COURSE",
									"EDIT GRADE OF A STUDENT",
									"VIEW A SCOREBOARD",
									"VIEW PROFILE INFO",
									"CHANGE PASSWORD",
									"LOGOUT" };

	vector<string> CLASS_MENU = { "IMPORT CLASS",
									"ADD NEW STUDENT",
									"EDIT EXIST STUDENT",
									"REMOVE A STUDENT",
									"VIEW LIST OF CLASSES",
									"CHANGE CLASS OF STUDENT",
									"RETURN" };

	vector<string> COURSES_MENU = {
								"CREATE ACADEMIC YEAR",
								"DELETE ACADEMIC YEAR",
								"CREATE SEMESTER",
								"DELETE SEMESTER",
								"IMPORT COURSE",
								"ADD NEW COURSE",
								"EDIT EXIST COURSE",
								"REMOVE COURSE",
								"REMOVE STUDENT FROM COURSE",
								"ADD STUDENT TO COURSE",
								"VIEW LIST OF COURSE",
								"VIEW ATTENDANCE OF COURSE",
								"CREATE NEW LECTURER",
								"VIEW ALL LECTURERS",
								"RETURN" };

	vector<string> CUDV_MENU = { "CREATE", "UPDATE", "DELETE", "VIEW", "RETURN" };

	vector<string> SCOREBOARD_MENU = { "VIEW SCOREBOARD", "EXPORT SCOREBOARD", "RETURN" };

	vector<string> ATTENDANCE_MENU = { "VIEW ATTENDANCE LIST", "EXPORT ATTENDANCE LIST", "RETURN" };
};

#endif // !NENU_H
