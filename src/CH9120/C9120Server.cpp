#include "CH9120/CH9120Server.h"
#include "HttpRequest.h"
#include "HttpParser.h"

using namespace Rp2040;

void CH9120Server::init(UCHAR serverIp[4], UCHAR gateway[4], UCHAR subnetMask[4], UWORD port, UDOUBLE baudRate)
{
    CH9120_SetMode(TcpServerMode);
    CH9120_SetLocalIp(serverIp);
    CH9120_SetGateway(gateway);
    CH9120_SetSubnetMask(subnetMask);
    CH9120_SetLocalPort(port);
    CH9120_SetBaudRate(baudRate);

    CH9120_Init();
}

String CH9120Server::getRawRequest()
{
    if (UART_ID1.available())
    {
        return UART_ID1.readString();
    }
    return String();
}

void CH9120Server::sendResponse(HttpResponse response)
{
    UART_ID1.print(response.toString());
}

void CH9120Server::handleRequest(HttpResponse (*callback)(HttpRequest) = nullptr)
{
    String rawRequest = getRawRequest();
    if (rawRequest == NULL || rawRequest == "")
    {
        // Serial.println("No data to handle");
        return;
    }

    if (callback != NULL)
    {
        HttpRequest request = HttpParser::GetHttpRequest(rawRequest);
        HttpResponse response = callback(request);
        sendResponse(response);
    }
}

void CH9120Server::handleRequest(IHttpHandler *handler)
{
    String rawRequest = getRawRequest();
    if (rawRequest == NULL || rawRequest == "")
    {
        // Serial.println("No data to handle");
        return;
    }

    if (handler != NULL)
    {
        HttpRequest request = HttpParser::GetHttpRequest(rawRequest);
        HttpResponse response = handler->handle(request);
        sendResponse(response);
    }
}