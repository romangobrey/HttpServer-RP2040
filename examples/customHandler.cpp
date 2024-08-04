#include <Arduino.h>
#include <HttpServer.h>
#include <HttpParser.h>

using namespace Rp2040;

namespace MyCustomHandlers
{
    class CustomHandler : public IHttpHandler
    {
    public:
        HttpResponse handle(const HttpRequest &request) override;
    };
}

using namespace MyCustomHandlers;

HttpResponse CustomHandler::handle(const HttpRequest &request)
{
    HttpResponse response;
    response.code = 200;
    response.codeDescription = "OK";
    response.body = "My custom response";

    response.headers["Connection"] = "close";
    response.headers["Content-Type"] = "text/plain";
    response.headers["Content-Length"] = response.body.length();

    return response;
}

HttpServer httpServer(DeviceModel::Rp2040Eth);
CustomHandler httpHandler;

void setup()
{
    Serial.begin(115200);
    Serial.println("init started");

    // Init HTTP server
    UCHAR serverIp[4] = {192, 168, 1, 170};
    httpServer.init(serverIp);

    Serial.println("init finished");
}

void loop()
{
    httpServer.handleRequest(&httpHandler);
}
