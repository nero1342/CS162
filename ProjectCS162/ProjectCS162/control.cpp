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


void NewStudentInfo(Student &x) {
	menu Menu;
	Menu.title = "NEW STUDENT INFOMATION";
	Menu.name.clear();
	Menu.name = { "StudentID:",
				"Lastname:",
				"Firstname:",
				"Gender:",
				"DoB:",
				"Class:",
				"Aplly",
				"Cancel"
	};
	Menu.minchosen = 1;
	Menu.chosen = 1;
	graphics show;
	window tool;
	show.init_graphic();
	Student tmp;
	tmp = x;
	int ok = 0;
	while (1) {
		show.show_menu(Menu, ok);
		ok = 1;
		int key;
		while (1) {
			key = menu_move(Menu);
			if (key == -1) Sleep(1);
			else break;
		}
		if (key) {
			if (Menu.chosen == 1) {
				tmp.SetStudentID(get_info(Menu, tmp.getStudentID()));
				continue;
			}
			if (Menu.chosen == 2) {
				tmp.SetLastname(get_info(Menu, tmp.getLastname()));
				continue;
			}
			if (Menu.chosen == 3) {
				tmp.SetFirstname(get_info(Menu, tmp.getFirstname()));
				continue;
			}
			if (Menu.chosen == 4) {
				tmp.SetGender(get_info(Menu, tmp.getGender()));
				continue;
			}
			if (Menu.chosen == 5) {
				tmp.SetDoB(get_info(Menu, tmp.getDoB()));
				continue;
			}
			if (Menu.chosen == 6) {
				tmp.SetClass(get_info(Menu, tmp.getClass()));
				continue;
			}
			if (Menu.chosen == 7) {
				x = tmp;
				return;
			}
			if (Menu.chosen == 8) {
				return;
			}
		}
	}
}

void EditInfo(Student &x) {
	menu Menu;
	Menu.title = "EDIT " + x.getStudentID() + " INFOMATION";
	Menu.name.clear();
	Menu.name = { "Lastname:",
				"Firstname:",
				"Gender:",
				"DoB:",
				"Aplly",
				"Cancel"
	};
	Menu.minchosen = 1;
	Menu.chosen = 1;
	graphics show;
	window tool;
	show.init_graphic();
	Student tmp;
	tmp = x;
	int ok = 0;
	while (1) {
		show.show_menu(Menu, ok);
		if (!ok) {
			tool.gotoXY(35, 1 + Menu.begin - 1);
			cout << tmp.getLastname();
			tool.gotoXY(35, 2 + Menu.begin - 1);
			cout << tmp.getFirstname();
			tool.gotoXY(35, 3 + Menu.begin - 1);
			cout << tmp.getGender();
			tool.gotoXY(35, 4 + Menu.begin - 1);
			cout << tmp.getDoB();
		}
		ok = 1;
		int key;
		while (1) {
			key = menu_move(Menu);
			if (key == -1) Sleep(1);
			else break;
		}
		if (key) {
			if (Menu.chosen == 1) {
				tmp.SetLastname(get_info(Menu, tmp.getLastname()));
				continue;
			}
			if (Menu.chosen == 2) {
				tmp.SetFirstname(get_info(Menu, tmp.getFirstname()));
				continue;
			}
			if (Menu.chosen == 3) {
				tmp.SetGender(get_info(Menu, tmp.getGender()));
				continue;
			}
			if (Menu.chosen == 4) {
				tmp.SetDoB(get_info(Menu, tmp.getDoB()));
				continue;
			}
			if (Menu.chosen == 5) {
				x = tmp;
				return;
			}
			if (Menu.chosen == 6) {
				return;
			}
		}
	}
}

string get_info(menu &Menu, string old) {
	string tmp = old;
	window tool;
	tool.gotoXY(100, Menu.chosen + Menu.begin - 1);
	cout << "<";
	tool.gotoXY(35, Menu.chosen + Menu.begin - 1);
	cout << tmp;
	while (1) {
		int key;
		while (1) {
			key = tool.inputkey();
			if (key == -1) Sleep(1);
			else break;
		}
		if (key == 8) {
			if (tmp.size())tmp.pop_back();
		}
		else if (key == 13) {
			tool.gotoXY(100, Menu.chosen + Menu.begin - 1);
			cout << " ";
			return tmp;
		}
		else if (key >= 32 && key <= 126) {
			if (tmp.size() == 20) continue;
			tmp = tmp + char(key);
		}
		tool.gotoXY(35, Menu.chosen + Menu.begin - 1);
		for (int i = 1; i <= 20; ++i)
			cout << " ";
		tool.gotoXY(35, Menu.chosen + Menu.begin - 1);
		cout << tmp;
	}
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