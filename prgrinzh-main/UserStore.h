#ifndef USERSTORE_H
#define USERSTORE_H

#include <string>
#include <unordered_map>

struct User {
    std::string passwordHash;
    std::string role;
};

class UserStore {
public:
    static UserStore& instance();

    void addUser(const std::string& username, const std::string& passwordHash, const std::string& role);
    bool validateUser(const std::string& username, const std::string& password) const;
    bool userExists(const std::string& username) const;

private:
    std::unordered_map<std::string, User> users;
    UserStore();

    static std::string hashPassword(const std::string& password);
};

#endif // USERSTORE_H
