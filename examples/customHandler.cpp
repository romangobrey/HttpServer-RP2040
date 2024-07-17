#include <Arduino.h>
#include <HttpServer.h>
#include <HttpParser.h>

using namespace Rp2040;

namespace MyCustomHandlers
{
    class CustomHandler : public IHttpHandler
    {
    public:
        void handle(const HttpRequest &request) override;
    };
}

using namespace MyCustomHandlers;

void CustomHandler::handle(const HttpRequest &request)
{
    HttpResponse response;
    response.headers["Connection"] = "close";
    response.headers["Content-Type"] = "text/plain";

    response.code = 200;
    response.codeDescription = "OK";
    response.body = "My custom response";

    response.headers["Content-Length"] = response.body.length();

    UART_ID1.print(response.toString());
}

HttpServer httpServer;
CustomHandler httpHandler;

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
    httpServer.handleRequest(&httpHandler);
}
