#ifndef AUTHSERVICE_H
#define AUTHSERVICE_H

#include <string>

class AuthService {
public:
    static std::string generateToken(const std::string& username);
};

#endif // AUTHSERVICE_H
