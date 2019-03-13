#include"graphics.h"

void graphics::init_graphic() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	SetConsoleDisplayMode(GetStdHandle(STD_OUTPUT_HANDLE), CONSOLE_FULLSCREEN_MODE, 0);
	srand(time(NULL));
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
	SetConsoleMode(hin, ENABLE_EXTENDED_FLAGS);
	SetConsoleMode(hin, ENABLE_WINDOW_INPUT | ENABLE_MOUSE_INPUT);
	window tool;
	tool.hide_pointer();
}

void graphics::show_menu(menu x,int ok) {
	window tool;
	if (ok == 0) {
		tool.clrscr();
		tool.gotoXY(35, 5);
		cout << x.title;
		for (int i = 0; i < x.name.size(); ++i) {
			tool.gotoXY(25, x.begin + i);
			cout << x.name[i];
		}
	}
	for (int i = 0; i < x.name.size(); ++i) {
		tool.gotoXY(22, x.begin + i);
		cout << " ";
	}
	tool.gotoXY(22, x.begin + x.chosen - 1);
	cout << ">";
	tool.gotoXY(25, 20);
}