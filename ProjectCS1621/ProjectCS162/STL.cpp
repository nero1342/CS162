#include "STL.hpp"
/*
bool getline(std::ifstream &fin, std::string &st) {
	char buffer[5000];
	fin.get(buffer, 5000, '\n');
	if (fin.fail()) return false;
	fin.ignore(10000, '\n');
	st = buffer;
	return true;
}
*/
void Import(string fileName,string link)
{
	char buffer[5000], tmp[5000];
	std::ifstream in(fileName);
	while (!fileName.empty() && fileName.back() != '.') fileName.pop_back();
	std::ofstream ou(link + fileName + "txt");

	in.get(buffer, 5000, '\n');
	in.ignore(1000, '\n');

	while (in.get(buffer, 5000, '\n'))
	{
		if (in.fail()) break;

		in.ignore(10000, '\n');
		int len = strlen(buffer), n = 0;

		for (int i = 0; i < len; ++i)
		{
			if (buffer[i] == ',')
			{
				tmp[n++] = '\0';
				ou << string(tmp) << '\n';
				n = 0;
			}
			else tmp[n++] = buffer[i];
		}
		tmp[n++] = '\0';
		ou << string(tmp) << '\n';
	}
}
