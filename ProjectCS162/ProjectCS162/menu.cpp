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
	now.chosen = now.minchosen = 1;
}

menu::menu():chosen(1) {}

menu::menu(string title, vector<string> &name, int minchosen) : title(title), name(name), chosen(minchosen), minchosen(minchosen) {
	//name.push_back("RETURN");
}

void menu::Assign(string _title, vector<string> &_name, int _minchosen) {
	title = _title;
	name = _name;
	minchosen = _minchosen;
}

int menu::maxLength() {
	int Max = 0;
	for (string & st : name) Max = max(Max, st.size());
	return Max;
}

int menu::startPointInfo()
{
	window Window;
	int maxLengthMenu = maxLength();
	int totalLength = maxLengthMenu + 2 + maxLengthInfo; // 2 is space
	int startPoint = (Window.GetColumns() - totalLength) / 2 + maxLengthMenu + 2;
	return startPoint;
}

int menu::endPointInfo()
{
	window Window;
	int maxLengthMenu = maxLength();
	int totalLength = maxLengthMenu + 2 + maxLengthInfo; // 2 is space
	int startPoint = (Window.GetColumns() - totalLength) / 2 + maxLengthMenu + 2;
	int endPoint = startPoint + maxLengthInfo + 5;
	return endPoint;
}

int menu::startPointTitle()
{
	window Window;
	int startPoint = (Window.GetColumns() - title.size()) / 2;
	return startPoint;
	return 0;
}

