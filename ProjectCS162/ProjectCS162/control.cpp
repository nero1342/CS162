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
				"Aplly",
				"Cancel"
	};
	Menu.minchosen = 1;
	Menu.chosen = 1;
	vector<string> answer;
	answer.clear();
	for (int i = 1; i <= 5; i++) answer.push_back("");
	if (fill_menu(Menu, answer) == 0) return;
	else {
		x.SetStudentID(answer[0]);
		x.SetLastname(answer[1]);
		x.SetFirstname(answer[2]);
		x.SetGender(answer[3]);
		x.SetDoB(answer[4]);
		return;
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
				"Apply",
				"Cancel"
	};
	Menu.minchosen = 1;
	Menu.chosen = 1;
	vector<string > answer;
	answer.clear();
	answer.push_back(x.getLastname());
	answer.push_back(x.getFirstname());
	answer.push_back(x.getGender());
	answer.push_back(x.getDoB());
	if (fill_menu(Menu, answer) == 0) return;
	else {
		x.SetLastname(answer[0]);
		x.SetFirstname(answer[1]);
		x.SetGender(answer[2]);
		x.SetDoB(answer[3]);
		return;
	}
}


string get_info(menu &Menu, string old) {
	string tmp = old;
	window tool;
	tool.gotoXY(100, Menu.chosen + Menu.begin - 1);
	cout << "<";
	tool.gotoXY(45, Menu.chosen + Menu.begin - 1);
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
		tool.gotoXY(45, Menu.chosen + Menu.begin - 1);
		for (int i = 1; i <= 20; ++i)
			cout << " ";
		tool.gotoXY(45, Menu.chosen + Menu.begin - 1);
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

bool fill_menu(menu &Menu, vector<string > &answer) {
	graphics show;
	window tool;
	show.init_graphic();
	int ok = 0;
	while (1) {
		show.show_menu(Menu, ok);
		if (!ok) {
			for (int i = 0; i < answer.size(); ++i) {
				tool.gotoXY(45, i + Menu.begin );
				cout << answer[i];
			}
		}
		ok = 1;
		int key;
		while (1) {
			key = menu_move(Menu);
			if (key == -1) Sleep(1);
			else break;
		}
		if (key) {
			if (Menu.chosen == Menu.name.size()) return 0;
			if (Menu.chosen == Menu.name.size() - 1) return 1;
			answer[Menu.chosen - 1] = get_info(Menu, answer[Menu.chosen - 1]);
		}
	}
}

void Message(string message) {
	window Window;
	Window.clrscr();
	int x = 1, y = 1;
	Window.gotoXY(x, y);
	cout << message;
	Window.gotoXY(x, y + 1);
	cout << "Press any key to continue...";
	while (Window.inputkey() == -1);
}