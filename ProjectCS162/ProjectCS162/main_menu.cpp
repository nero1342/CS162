#include"main_menu.h"

void Main_menu() {
	menu main_menu;
	main_menu.chosen = 1;
	main_menu.title = "STUDENT MANAGER SYSTEM";
	main_menu.name.clear();
	main_menu.name.push_back("login");
	main_menu.name.push_back("exit");
	graphics show;
	show.init_graphic();
	int ok = 0;
	while (1) {
		show.show_menu(main_menu,ok);
		ok = 1;
		int key;
		while (1) {
			key = menu_move(main_menu);
			if (key == -1) Sleep(1);
			else break;
		}
		if (key){
			if (main_menu.chosen == 1) {
				login X;
				if (X.login_menu()) {
					window tool;
					tool.clrscr();
					ok = 0;
					continue;
				}
			}
			return;
		}
	}
}