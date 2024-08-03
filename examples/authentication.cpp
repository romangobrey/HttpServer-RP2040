#include <Arduino.h>
#include <HttpServer.h>

using namespace Rp2040;

HttpResponse handleRequest(HttpRequest request);

HttpServer httpServer(DeviceModel::Rp2040Eth);

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