#ifndef STL_hpp
#define STL_hpp

#include <vector>
#include <fstream>
#include <map>
#include <iostream>
#include <fstream>

std::ofstream& operator<<(std::ofstream& ou, std::string s);

std::ifstream& operator>>(std::ifstream& in, std::string & s);

#endif // STL_hpp