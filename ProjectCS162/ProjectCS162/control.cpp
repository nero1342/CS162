#include"control.h"


int menu_move(menu &x) {
	window move;
	int key = move.inputkey();
	if (key == -1) return key;
	if (key == 72) if (x.chosen != 1) x.chosen--;
	if (key == 80) if (x.chosen != x.name.size()) x.chosen++;
	if (key == 13) return 1;
	return 0;
}