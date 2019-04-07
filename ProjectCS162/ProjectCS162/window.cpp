#include"window.h"


long long window::Rand(long long l, long long h) {
	return l + ((long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) * (RAND_MAX + 1) +
		(long long)rand() * (RAND_MAX + 1) * (RAND_MAX + 1) +
		(long long)rand() * (RAND_MAX + 1) +
		rand()) % (h - l + 1);
}

int window::inputkey() {
	if (_kbhit()) {
		int key = _getch();
		return key;
	}
	return -1;
}

void window::absorb_input() {
	while (inputkey() != -1) {}
}

void window::clrscr() {
	CONSOLE_SCREEN_BUFFER_INFO	csbiInfo;
	HANDLE	hConsoleOut;
	COORD	Home = { 0,0 };
	DWORD	dummy;
	hConsoleOut = GetStdHandle(STD_OUTPUT_HANDLE);
	GetConsoleScreenBufferInfo(hConsoleOut, &csbiInfo);
	FillConsoleOutputCharacter(hConsoleOut, ' ', csbiInfo.dwSize.X * csbiInfo.dwSize.Y, Home, &dummy);
	csbiInfo.dwCursorPosition.X = 0;
	csbiInfo.dwCursorPosition.Y = 0;
	SetConsoleCursorPosition(hConsoleOut, csbiInfo.dwCursorPosition);
}

void window::gotoXY(int x, int y) {
	static HANDLE h = NULL;
	if (!h)
		h = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD c = { x, y };
	SetConsoleCursorPosition(h, c);
}

void window::text_color(int color) {

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void window::appear_pointer() {
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = 1;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}

void window::hide_pointer() {
	HANDLE hOut;
	CONSOLE_CURSOR_INFO ConCurInf;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = 0;
	SetConsoleCursorInfo(hOut, &ConCurInf);
}


#define HOUT GetStdHandle(STD_OUTPUT_HANDLE)
int window::GetRows() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;

	GetConsoleScreenBufferInfo(HOUT, &csbi);
	return csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
}

int window::GetColumns() {
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(HOUT, &csbi);
	return csbi.srWindow.Right - csbi.srWindow.Left + 1;
}
