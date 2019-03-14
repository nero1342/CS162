#include"login.h"

int login::login_menu() {
	login data;
	menu login_menu;
	login_menu.title = "LOGIN";
	login_menu.chosen = 1;
	login_menu.name.push_back("USER");
	login_menu.name.push_back("PASSWORD");
	login_menu.name.push_back("enter");
	login_menu.name.push_back("return");
	graphics show;
	show.init_graphic();
	int ok = 0;
	while (1) {
		show.show_menu(login_menu, ok);
		ok = 1;
		int key;
		while (1) {
			key = menu_move(login_menu);
			if (key == -1) Sleep(1);
			else break;
		}
		if (key) {
			if (login_menu.chosen == 1) {
				data.user = data.get_user(login_menu);
				continue;
			}
			if (login_menu.chosen == 2) {
				data.password = data.get_password(login_menu);
				continue;
			}
			if (login_menu.chosen == 3) {
				//check(data);
				window tool;
				tool.gotoXY(35, 20);
				cout << data.user;
				tool.gotoXY(35, 21);
				cout << data.password;
				continue;
			}
			return 1;
		}
	}
	return 0;
}

string login::get_user(menu &login_menu) {
	string tmp = "";
	window tool;
	tool.gotoXY(100, login_menu.chosen + login_menu.begin - 1);
	cout << "<";
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
			tool.gotoXY(100, login_menu.chosen + login_menu.begin - 1);
			cout << " ";
			return tmp;
		}
		else if ((key>='a'&&key<='z')||(key>='A'&&key<='Z')||(key>='0'&&key<='9')){
			if (tmp.size() == 30) continue;
			tmp = tmp + char(key);
		}
		tool.gotoXY(35, login_menu.chosen + login_menu.begin - 1);
		for (int i = 1; i <= 30; ++i)
			cout << " ";
		tool.gotoXY(35, login_menu.chosen + login_menu.begin - 1);
		cout << tmp;
	}
}

string login::get_password(menu &login_menu) {
	string tmp = "";
	window tool;
	tool.gotoXY(100,login_menu.chosen + login_menu.begin - 1);
	cout << "<";
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
			tool.gotoXY(100, login_menu.chosen + login_menu.begin - 1);
			cout << " ";
			return tmp;
		}
		else if ((key >= 'a'&&key <= 'z') || (key >= 'A'&&key <= 'Z') || (key >= '0'&&key <= '9')) {
			if (tmp.size() == 30) continue;
			tmp = tmp + char(key);
		}
		tool.gotoXY(35, login_menu.chosen + login_menu.begin - 1);
		for (int i = 1; i <= 30; ++i)
			cout << " ";
		tool.gotoXY(35, login_menu.chosen + login_menu.begin - 1);
		for (int i = 0; i < tmp.size(); ++i)
			cout << "*";
	}
}