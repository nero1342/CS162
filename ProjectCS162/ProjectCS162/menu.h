#pragma once
#ifndef NENU_H
#define MENU_H
#include<iostream>
#include<string>
#include<vector>
using namespace std;
struct menu {
	string title;
	vector<string > name;
	int chosen;
	const int begin = 15;
};
#endif // !NENU_H
