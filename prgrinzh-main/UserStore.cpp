#include "UserStore.h"

UserStore::UserStore() {
    users["admin"] = { "secret", "admin" };
}

UserStore& UserStore::instance() {
    static UserStore store;
    return store;
}

void UserStore::addUser(const std::string& username, const std::string& passwordHash, const std::string& role) {
    users[username] = { passwordHash, role };
}

bool UserStore::validateUser(const std::string& username, const std::string& password) const {
    auto it = users.find(username);
    if (it == users.end()) return false;
    return it->second.passwordHash == hashPassword(password);
}

bool UserStore::userExists(const std::string& username) const {
    return users.find(username) != users.end();
}

std::string UserStore::hashPassword(const std::string& password) {
    return password; // для упрощения пока просто возвращаем
}
