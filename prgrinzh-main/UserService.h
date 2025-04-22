#ifndef USERSERVICE_H
#define USERSERVICE_H

#include <Poco/Net/HTTPRequestHandler.h>

class UserService : public Poco::Net::HTTPRequestHandler {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request,
        Poco::Net::HTTPServerResponse& response) override;
};

#endif
