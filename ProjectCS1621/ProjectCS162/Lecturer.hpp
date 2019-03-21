#ifndef Lecturer_hpp
#define Lecturer_hpp

#include <iostream>

using namespace std;

class Lecturer {
private:
    string Name;
public:
	Lecturer();
	Lecturer(string Name);
	string getName(); 

};

#endif /* Lecturer_hpp */
