#pragma once
#ifndef LOGIN_H
#define LOGIN_H

#include<iostream>
#include<string>
#include"window.h"
#include"menu.h"
#include"graphics.h"
#include"control.h"
#include"Account.hpp"
#include"AccountList.hpp"

using namespace std;

struct login {
	string user, password;
	string login_menu(AccountList &acclist);
	string get_user(menu &login_menu);
	string get_password(menu &login_menu);
};
#endif // !LOGIN_H
