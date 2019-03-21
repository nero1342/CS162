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

	menu();
	menu(string title, vector<string> &name, int minchosen);
};

void staff_menu(menu &now);



class MenuFunction {
public:
	vector<string> STAFF_MENU = { "CLASS",
									"COURSES",
									"SCOREBOARD",
									"ATTENDANCE LIST",
									"LOGOUT" };
	vector<string> STUDENT_MENU = { "CLASS",
									"COURSES",
									"SCOREBOARD",
									"ATTENDANCE LIST",
									"RETURN" };
	vector<string> LECTURER_MENU = { "CLASS",
									"COURSES",
									"SCOREBOARD",
									"ATTENDANCE LIST",
									"RETURN" };
	vector<string> CLASS_MENU = { "IMPORT CLASS",
									"EDIT EXIST STUDENT",
									"REMOVE A STUDENT",
									"VIEW LIST OF CLASSES",
									"CHANGE CLASS OF STUDENT",
									"RETURN" };
};

#endif // !NENU_H
