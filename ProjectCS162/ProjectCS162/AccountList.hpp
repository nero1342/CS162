#ifndef AccountList_hpp
#define AccountList_hpp

#include "STL.hpp"
#include <fstream>
#include "Account.hpp"
#include "Student.hpp"
#include "Lecturer.hpp"

class AccountList {
private:
    vector<Account> list;
public:
    bool isExist(string username);
    void Add(Student student);
    void Add(Lecturer lecturer);
    bool Login(string username, string password);
    void Remove(string username);

    void LoadData();
    void SaveData();

    void ImportClass(string Class);
};

#endif /* AccountList_hpp */
