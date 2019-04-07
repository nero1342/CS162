#pragma once
#ifndef GRAPHICS_H
#define GRAPHICS_H
#include"window.h"
#include"menu.h"
struct graphics {
	void init_graphic();
	void show_menu(menu &x,int ok);
};

#endif // !GRAPHICS_H
