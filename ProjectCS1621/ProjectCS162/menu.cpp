#include"menu.h"

void staff_menu(menu &now) {
	now.title = "STAFF menu";
	now.name.push_back("Import Class");
	now.name.push_back("Add New Student");
	now.name.push_back("Edit Exist Student");
	now.name.push_back("Remove A Student");
	now.name.push_back("View List Classes");
	now.name.push_back("Change class of student");
	//now.name.push_back("Import Course");
	now.name.push_back("Logout");
	now.chosen = 1;
}

menu::menu():chosen(1) {}

menu::menu(string title, vector<string> &name, int minchosen) : title(title), name(name), chosen(minchosen), minchosen(minchosen) {}
