#include "STL.hpp"

std::ofstream & operator<<(std::ofstream & ou, std::string s)
{
	for (int i = 0; i < s.length(); ++i) ou << s[i];
	return ou;
}

std::ifstream & operator>>(std::ifstream & in, std::string & s)
{
	s = "";
	char x;
	while (in >> x && x != ' ' && x != '\n') s += x;
	return in;
}

