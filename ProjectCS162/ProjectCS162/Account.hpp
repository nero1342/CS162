#ifndef Account_hpp
#define Account_hpp

#include <iostream>

using namespace std;

struct Account {
    string username, password, type, Class;
    
    Account();
    Account(string username, string password, string type, string Class);
};

#endif /* Account_hpp */