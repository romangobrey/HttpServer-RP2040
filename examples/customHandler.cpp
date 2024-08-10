#include <Arduino.h>
#include <HttpServer.h>
#include <HttpParser.h>
#include "..\configuration\W5500EvbPico.h"

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

HttpServer httpServer(Config_DeviceModel);
CustomHandler httpHandler;

void setup()
{
    Serial.begin(115200);
    Serial.println("init started");
    httpServer.init(Config_ServerIp);
    Serial.println("init finished");
}

void loop()
{
    httpServer.handleRequest(&httpHandler);
}
