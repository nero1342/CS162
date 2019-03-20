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

#endif // !NENU_H
