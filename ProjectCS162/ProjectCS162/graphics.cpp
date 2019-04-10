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
	tool.clrscr();
}

void graphics::show_menu(menu &x,int ok) {
	window tool;
	int startPointMenu = x.startPointInfo() - x.maxLength() - 2;
	if (ok == 0) {
		tool.clrscr();
		tool.gotoXY(x.startPointTitle(), 5);
		tool.background(1);
	//	tool.text_color(14);
		cout << x.title;
		tool.background(0);
	//	tool.text_color(15);
		for (int i = 0; i < x.name.size(); ++i) {
			tool.gotoXY(startPointMenu, x.begin + i);
			cout << x.name[i];
		}
	}
	for (int i = 0; i < x.name.size(); ++i) {
		tool.gotoXY(startPointMenu - 3, x.begin + i);
		cout << " ";
	}
	tool.gotoXY(startPointMenu - 3, x.begin + x.chosen - 1);
	cout << ">";
	tool.gotoXY(startPointMenu, 20);
}