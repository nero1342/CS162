#ifndef AccountList_hpp
#define AccountList_hpp

#include <fstream>
#include <vector>
#include "Account.hpp"
#include "Student.hpp"
#include "Lecturer.hpp"

class AccountList {
private:
    vector<Account> list;
public:
    //bool isExist(string username);
    void Add(Student student);
    void Add(Lecturer lecturer);
    //void Remove(string username);
};

#endif /* AccountList_hpp */
