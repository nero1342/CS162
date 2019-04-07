#pragma once
#ifndef CONTROL_H
#define CONTROL_H

#include"window.h"
#include"graphics.h"
#include"student.hpp"
#include"menu.h"

int menu_move(menu &x);

string menu_choose(menu &main_menu);

void NewStudentInfo(Student &x);
string get_info(menu &Menu, string old);
void EditInfo(Student &x);
bool fill_menu(menu &Menu, vector<string > &anwser, bool isPassword = false);

void Message(string message);

void Guide(vector<string> v_guide);

#endif // !CONTROL_H
