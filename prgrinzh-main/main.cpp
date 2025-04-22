#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <iostream>

#include "UserService.h"

using namespace Poco::Net;
using namespace Poco::Util;

class UserServiceFactory : public HTTPRequestHandlerFactory {
public:
    HTTPRequestHandler* createRequestHandler(const HTTPServerRequest&) override {
        return new UserService();
    }
};

class WebServerApp : public ServerApplication {
protected:
    int main(const std::vector<std::string>& args) override {
        HTTPServerParams::Ptr pParams = new HTTPServerParams;
        ServerSocket socket(8080);

        HTTPServer server(new UserServiceFactory, socket, pParams);
        std::cout << "UserService started at http://localhost:8080" << std::endl;

        server.start();
        waitForTerminationRequest();
        server.stop();

        return Application::EXIT_OK;
    }
};

int main(int argc, char** argv) {
    WebServerApp app;
    std::cout << "Running WebServerApp..." << std::endl;
    return app.run(argc, argv);
}

