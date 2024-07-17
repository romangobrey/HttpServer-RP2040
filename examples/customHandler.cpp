#include <Arduino.h>
#include <HttpServer.h>
#include <HttpParser.h>

using namespace Rp2040;

namespace MyCustomHandlers
{
    class CustomHandler : public IHttpHandler
    {
    public:
      void handle(HttpRequest &request);
    };
}

using namespace MyCustomHandlers;

void CustomHandler::handle(HttpRequest &request)
{
    Serial.println("CustomHandlers::CustomHandler::handle!!!!!");
}

HttpServer httpServer;
CustomHandler httpHandler;
IHttpHandler *httpHandlerPointer = &httpHandler;

void setup()
{
    Serial.begin(115200);
    Serial.println("init started");

    // Init HTTP server
    UCHAR serverIp[4] = {192, 168, 1, 170};
    UCHAR gateway[4] = {192, 168, 1, 1};
    UCHAR subnetMask[4] = {255, 255, 255, 0};

    httpServer.init(serverIp, gateway, subnetMask);

    Serial.println("init finished");
}

void loop()
{
    httpServer.handleRequest(httpHandlerPointer);
}
