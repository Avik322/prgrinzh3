#include "AuthService.h"
#include <jwt-cpp/jwt.h>

std::string AuthService::generateToken(const std::string& username) {
    auto token = jwt::create()
        .set_issuer("auth0")
        .set_type("JWS")
        .set_payload_claim("username", jwt::claim(username))
        .sign(jwt::algorithm::hs256{ "secret" });

    return token;
}
