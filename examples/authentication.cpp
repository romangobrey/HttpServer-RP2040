#include <Arduino.h>
#include <HttpServer.h>
#include "..\configuration\Rp2040Eth.h"

using namespace Rp2040;

HttpResponse handleRequest(HttpRequest request);
HttpServer httpServer(Config_DeviceModel);

void setup()
{
    Serial.begin(115200);
    Serial.println("init started");
    httpServer.init(Config_ServerIp);
    Serial.println("init finished");
}

void loop()
{
    httpServer.handleRequest(&handleRequest);
}

HttpResponse handleRequest(HttpRequest request)
{
    HttpResponse response;
    response.headers["Connection"] = "close";
    response.headers["Content-Type"] = "text/plain";

    if (request.methodType == HttpMethodType::GET && request.methodName == "getData")
    {
        if (request.headers["Authorization"] == "Basic dXNlcjpwYXNz") // UserName: user, Password: pass
        {
            response.code = 200;
            response.codeDescription = "OK";
            response.body = "Some data to return";
            response.headers["Content-Length"] = response.body.length();

            return response;
        }
        else
        {
            response.code = 403;
            response.codeDescription = "Forbidden";
            response.headers["Content-Length"] = "0";

            return response;
        }
    }

    response.code = 405;
    response.codeDescription = "Method Not Allowed";
    response.headers["Allow"] = "GET";
    response.headers["Content-Length"] = "0";

    return response;
}