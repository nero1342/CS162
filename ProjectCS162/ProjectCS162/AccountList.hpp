#ifndef AccountList_hpp
#define AccountList_hpp

#include <vector>
#include "Account.hpp"
#include "Student.hpp"
#include "Lecturer.hpp"

class AccountList {
    vector<Account> list;
    
    bool isExist(string username);
    void Add(Student student);
    void Add(Lecturer lecturer);
    void Remove(string username);
};

#endif /* AccountList_hpp */
