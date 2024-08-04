#include "HttpServer.h"
#include "HttpRequest.h"
#include "HttpParser.h"

using namespace Rp2040;

Rp2040::HttpServer::HttpServer(DeviceModel device)
{
    deviceModel = device;
}

void Rp2040::HttpServer::init(UCHAR serverIp[4], UWORD port)
{
    switch (deviceModel)
    {
    case DeviceModel::Rp2040Eth:
        ch9120Server.init(serverIp, port);
        break;

    case DeviceModel::W5500EvbPico:
        w5500Server.init(serverIp, port);
        break;

    default:
        Serial.println("This device is not yet supported");
        break;
    }

    isInitialized = true;
}

void Rp2040::HttpServer::handleRequest(HttpResponse (*callback)(HttpRequest) = nullptr)
{
    if (!Rp2040::HttpServer::isInitialized)
    {
        return; // throw exception?
    }

    switch (deviceModel)
    {
    case DeviceModel::Rp2040Eth:
        ch9120Server.handleRequest(callback);
        break;

    case DeviceModel::W5500EvbPico:
        w5500Server.handleRequest(callback);
        break;

    default:
        Serial.println("This device is not yet supported");
        break;
    }
}

void Rp2040::HttpServer::handleRequest(IHttpHandler *handler)
{
    if (!Rp2040::HttpServer::isInitialized)
    {
        return; // throw exception?
    }

    switch (deviceModel)
    {
    case DeviceModel::Rp2040Eth:
        ch9120Server.handleRequest(handler);
        break;

    case DeviceModel::W5500EvbPico:
        w5500Server.handleRequest(handler);
        break;

    default:
        Serial.println("This device is not yet supported");
        break;
    }
}