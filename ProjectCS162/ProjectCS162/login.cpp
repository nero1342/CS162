#include"login.h"

string login::login_menu(AccountList &acclist) {
	menu log_menu;
	log_menu.maxLengthInfo = 30;
	log_menu.title = "LOGIN";
	log_menu.chosen = log_menu.minchosen = 1;
	log_menu.name.push_back("USERNAME:");
	log_menu.name.push_back("PASSWORD:");
	log_menu.name.push_back("ENTER");
	log_menu.name.push_back("EXIT");
	graphics show;
	window tool;
	show.init_graphic();
	int ok = 0;
	while (1) {
		show.show_menu(log_menu, ok);
		Guide({ 
			"Press Enter at line USERNAME/PASSWORD to type",
			"Choose ENTER to Login"
			 });
		ok = 1;
		int key;
		while (1) {
			key = menu_move(log_menu);
			if (key == -1) Sleep(1);
			else break;
		}
		if (key) {
			if (log_menu.chosen == 1) {
				user = get_user(log_menu);
				continue;
			}
			if (log_menu.chosen == 2) {
				password = get_password(log_menu);
				continue;
			}
			if (log_menu.chosen == 3) {
				if (acclist.Login(user, password)) return user;
				Message("Invalid username or password.");
				ok = 0;
				continue;
			}
			if (log_menu.chosen == 4) {
				exit(0);
			}
		}
	}
	return "";
}

string get_user(menu &login_menu) {
	string tmp = "";
	window tool;
	int startPoint = login_menu.startPointInfo();
	int endPoint = login_menu.endPointInfo();

	tool.gotoXY(endPoint, login_menu.chosen + login_menu.begin - 1);
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
			tool.gotoXY(endPoint, login_menu.chosen + login_menu.begin - 1);
			cout << " ";
			return tmp;
		}
		else if (key >= 33 && key <= 126) {
			if (tmp.size() == login_menu.maxLengthInfo) continue;
			tmp = tmp + char(key);
		}
		tool.gotoXY(startPoint, login_menu.chosen + login_menu.begin - 1);
		for (int i = 1; i <= endPoint - startPoint; ++i)
			cout << " ";
		tool.gotoXY(startPoint, login_menu.chosen + login_menu.begin - 1);
		cout << tmp;
	}
}

string get_password(menu &login_menu) {
	string tmp = "";
	window tool;
	int startPoint = login_menu.startPointInfo();
	int endPoint = login_menu.endPointInfo();

	tool.gotoXY(endPoint, login_menu.chosen + login_menu.begin - 1);
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
			tool.gotoXY(endPoint, login_menu.chosen + login_menu.begin - 1);
			cout << " ";
			return tmp;
		}
		else if (key >= 33 && key <= 126) {
			if (tmp.size() == login_menu.maxLengthInfo) continue;
			tmp = tmp + char(key);
		}
		tool.gotoXY(startPoint, login_menu.chosen + login_menu.begin - 1);
		for (int i = 1; i <= endPoint - startPoint; ++i)
			cout << " ";
		tool.gotoXY(startPoint, login_menu.chosen + login_menu.begin - 1);
		for (int i = 0; i < tmp.size(); ++i)
			cout << "*";
	}
}