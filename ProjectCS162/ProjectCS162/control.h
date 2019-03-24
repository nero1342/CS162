#pragma once
#ifndef CONTROL_H
#define CONTROL_H

#include"window.h"
#include"menu.h"
#include"graphics.h"
#include"student.hpp"

int menu_move(menu &x);

string menu_choose(menu &main_menu);

void NewStudentInfo(Student &x);
string get_info(menu &Menu, string old);
void EditInfo(Student &x);

#endif // !CONTROL_H
