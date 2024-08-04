#include <Arduino.h>
#include "HttpServer.h"
#include "HttpParser.h"

using namespace Rp2040;

HttpResponse handleRequest(HttpRequest request);

HttpServer httpServer(DeviceModel::W5500EvbPico);

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
    httpServer.handleRequest(&handleRequest);
}

HttpResponse handleGetRequest(HttpRequest request)
{
    HttpResponse response;
    response.headers["Connection"] = "close";
    response.headers["Content-Type"] = "text/plain";

    if (request.methodName == "getData")
    {
        bool isAuthorized = request.headers["Authorization"] == "Basic dXNlcjpwYXNz"; // UserName: user, Password: pass

        if (!isAuthorized)
        {
            response.code = 403;
            response.codeDescription = "Forbidden";
            response.body = "";
        }
        else
        {
            response.code = 200;
            response.codeDescription = "OK";
            response.body = "Some data to return";
        }
    }
    else
    {
        response.code = 405;
        response.codeDescription = "Method Not Allowed";
        response.body = "";
    }

    response.headers["Content-Length"] = response.body.length();
    return response;
}

HttpResponse handleHeadRequest(HttpRequest request)
{
    HttpResponse response;
    response.headers["Connection"] = "close";
    response.code = 200;
    response.codeDescription = "OK";
    return response;
}

HttpResponse handleOtherRequest(HttpRequest request)
{
    HttpResponse response;
    response.headers["Connection"] = "close";
    response.headers["Content-Type"] = "text/plain";

    response.code = 200;
    response.codeDescription = "OK";
    response.body = "";
    response.body += "Got " + HttpParser::GetRawMethodType(request.methodType) + " method type";
    response.body += "\r\n";
    response.body += "Got " + request.methodName + " method";

    response.headers["Content-Length"] = response.body.length();
    return response;
}

HttpResponse handleRequest(HttpRequest request)
{
    switch (request.methodType)
    {
    case HttpMethodType::GET:
        return handleGetRequest(request);

    case HttpMethodType::HEAD:
        return handleHeadRequest(request);

    default:
        return handleOtherRequest(request);
    }
}