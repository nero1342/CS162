#include"control.h"


int menu_move(menu &x) {
	window move;
	int key = move.inputkey();
	if (key == -1) return key;
	if (key == 72) if (x.chosen != x.minchosen) x.chosen--;
	if (key == 80) if (x.chosen != x.name.size()) x.chosen++;
	if (key == 13) return 1;
	return 0;
}

string menu_choose(menu &main_menu) {
	graphics show;
	window tool;
	show.init_graphic();
	int ok = 0;
	while (1) {
		show.show_menu(main_menu, ok);
		ok = 1;
		int key;
		while (1) {
			key = menu_move(main_menu);
			if (key == -1) Sleep(1);
			else break;
		}
		if (key) {
			return main_menu.name[main_menu.chosen - 1];
		}
	}
}