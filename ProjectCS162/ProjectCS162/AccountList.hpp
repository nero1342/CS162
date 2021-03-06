#ifndef AccountList_hpp
#define AccountList_hpp

#include "STL.hpp"
#include "Account.hpp"
#include "Student.hpp"
#include "Lecturer.hpp"

class AccountList {
private:
    vector<Account> list;
public:

	Account Find(string &username);
	void ChangePass(string username, string newPassword);
    bool isExist(string username);
    void Remove(string username);

	void Add(Account account);

    void Add(Student student);
    void Edit(Student student);

    void Add(Lecturer lecturer);
    
    bool Login(string username, string password);
    
    void Reload();
    void SaveData();

    void ImportClass(string Class);
};

#endif /* AccountList_hpp */
