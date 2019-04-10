#include "Account.hpp"
#include "SHA1.hpp"

Account::Account() {}

Account::Account(string username, string password, string type, string link)
    :username(username), password(password), type(type), link(link) {}

string Account::getUsername() {
    return username;
}

string Account::getPassword() {
    return password;
}

string Account::getType() {
    return type;
}

string Account::getLink() {
    return link;
}


bool Account::Login(string user, string pass) {
    return user == username && HashPassword(pass) == password;
}

void Account::EditLink(string newLink) {
    link = newLink;
}

void Account::ChangePassword(string newPassword)
{
	password = HashPassword(newPassword);
}

string HashPassword(string password) {
	SHA1 checksum;
	checksum.update(password);
	return checksum.final();
}