#ifndef STL_hpp
#define STL_hpp

#include <vector>
#include <fstream>
#include <map>
#include <iostream>
#include <fstream>
#include <Windows.h>

using namespace std;

std::ofstream& operator<<(std::ofstream& ou, std::string s);

std::ifstream& operator>>(std::ifstream& in, std::string & s);

bool getline(std::ifstream &fin, std::string &st);

void Import(string fileName);

#endif // STL_hpp