#include "Account.hpp"

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

void Account::ViewProfile() {

}

void Account::EditLink(string newLink) {
    link = newLink;
}

string HashPassword(string password) {
    return password;
}