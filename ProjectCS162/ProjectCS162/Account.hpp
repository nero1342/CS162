#ifndef Account_hpp
#define Account_hpp

#include <iostream>

using namespace std;

struct Account {
private:
    string username, password, type, Class;
public:
    Account();
    Account(string username, string password, string type, string Class);
};

#endif /* Account_hpp */
