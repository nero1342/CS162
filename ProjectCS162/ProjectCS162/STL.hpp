#ifndef STL_hpp
#define STL_hpp

#include <vector>
#include <fstream>
#include <map>
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <string>

using namespace std;

//bool getline(std::ifstream &fin, std::string &st);

void Import(string fileName,string link);

void Export(vector<string> &row, vector<string> &col, string name, vector<vector<int>> &a);

#endif // STL_hpp