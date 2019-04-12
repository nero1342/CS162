#ifndef Account_hpp
#define Account_hpp

#include <iostream>

using namespace std;

struct Account {
private:
    string username, password, type, link;
public:
    Account();
    Account(string username, string password, string type, string link);

    string getUsername();
    string getPassword();
    string getType();
    string getLink();
    
    bool Login(string user, string pass);
    void EditLink(string newLink);
    void ChangePassword(string newPassword);
};

string HashPassword(string password);


#endif /* Account_hpp */
