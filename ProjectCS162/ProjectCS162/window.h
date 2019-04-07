#pragma once
#ifndef WINDOW_H
#define WINDOW_H

#include<iostream>
#include<conio.h>
#include<windows.h>
#include<stdio.h>
#include<iomanip>
#include<fstream>

using namespace std;

struct point {
	int x, y;
};

struct window{
	int F[10] = { 0,59,60,61,62,63,64,65,66,67 };
	int key;
	long long Rand(long long l,long long h);
	int inputkey();
	void absorb_input();
	void clrscr();
	void gotoXY(int x, int y);
	void text_color(int color);
	void appear_pointer();
	void hide_pointer();
	int GetRows();
	int GetColumns();
};
#endif // !WINDOW_H
