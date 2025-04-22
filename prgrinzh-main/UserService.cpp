#include "UserService.h"
#include "UserStore.h"
#include "AuthService.h"

#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <Poco/Dynamic/Var.h>

#include <iostream>
#include <sstream>

using namespace Poco::Net;
using namespace Poco::JSON;
using namespace Poco::Dynamic;

void UserService::handleRequest(HTTPServerRequest& request, HTTPServerResponse& response) {
    std::ostream& out = response.send();
    response.setContentType("application/json");

    if (request.getMethod() == HTTPRequest::HTTP_POST && request.getURI() == "/auth/token") {
        std::stringstream bodyStream;
        Poco::StreamCopier::copyStream(request.stream(), bodyStream);

        Parser parser;
        Var result = parser.parse(bodyStream);
        Object::Ptr body = result.extract<Object::Ptr>();

        std::string username = body->getValue<std::string>("username");
        std::string password = body->getValue<std::string>("password");

        if (UserStore::instance().validateUser(username, password)) {
            std::string token = AuthService::generateToken(username);

            Object responseObj;
            responseObj.set("token", token);
            response.setStatus(HTTPResponse::HTTP_OK);
            responseObj.stringify(out);
        }
        else {
            Object err;
            err.set("error", "Invalid credentials");
            response.setStatus(HTTPResponse::HTTP_UNAUTHORIZED);
            err.stringify(out);
        }
    }

    else if (request.getMethod() == HTTPRequest::HTTP_POST && request.getURI() == "/users") {
        std::stringstream bodyStream;
        Poco::StreamCopier::copyStream(request.stream(), bodyStream);

        Parser parser;
        Var result = parser.parse(bodyStream);
        Object::Ptr body = result.extract<Object::Ptr>();

        std::string username = body->getValue<std::string>("username");
        std::string password = body->getValue<std::string>("password");
        std::string role = body->has("role") ? body->getValue<std::string>("role") : "user";

        if (UserStore::instance().userExists(username)) {
            Object err;
            err.set("error", "User already exists");
            response.setStatus(HTTPResponse::HTTP_CONFLICT);
            err.stringify(out);
        }
        else {
            UserStore::instance().addUser(username, password, role);
            Object msg;
            msg.set("status", "User created");
            response.setStatus(HTTPResponse::HTTP_CREATED);
            msg.stringify(out);
        }
    }

    else if (request.getMethod() == HTTPRequest::HTTP_GET && request.getURI().find("/users/login/") == 0) {
        std::string login = request.getURI().substr(std::string("/users/login/").length());

        if (UserStore::instance().userExists(login)) {
            Object user;
            user.set("username", login);
            response.setStatus(HTTPResponse::HTTP_OK);
            user.stringify(out);
        }
        else {
            Object err;
            err.set("error", "User not found");
            response.setStatus(HTTPResponse::HTTP_NOT_FOUND);
            err.stringify(out);
        }
    }

    else {
        Object err;
        err.set("error", "Unsupported method or path");
        response.setStatus(HTTPResponse::HTTP_BAD_REQUEST);
        err.stringify(out);
    }
}

