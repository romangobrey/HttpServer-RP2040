#include "HttpServer.h"
#include "HttpRequest.h"
#include "HttpParser.h"

using namespace Rp2040;

Rp2040::HttpServer::HttpServer(DeviceModel device)
{
    deviceModel = device;
}

void Rp2040::HttpServer::init(UCHAR serverIp[4], UCHAR gateway[4], UCHAR subnetMask[4], UWORD port, UDOUBLE baudRate)
{
    if (deviceModel == DeviceModel::Rp2040Eth)
    {
        ch9120Server.init(serverIp, gateway, subnetMask, port, baudRate);
    }

    if (deviceModel == DeviceModel::W5500EvbPico)
    {
        w5500Server.init(serverIp, gateway, subnetMask, port);
    }

    isInitialized = true;
}

void Rp2040::HttpServer::handleRequest(HttpResponse (*callback)(HttpRequest) = nullptr)
{
    if (!Rp2040::HttpServer::isInitialized)
    {
        return; // throw exception?
    }

    if (deviceModel == DeviceModel::W5500EvbPico)
    {
        w5500Server.handleRequest(callback);
    }

    if (deviceModel == DeviceModel::Rp2040Eth)
    {
        ch9120Server.handleRequest(callback);
    }
}

void Rp2040::HttpServer::handleRequest(IHttpHandler *handler)
{
    if (!Rp2040::HttpServer::isInitialized)
    {
        return; // throw exception?
    }

    if (deviceModel == DeviceModel::W5500EvbPico)
    {
        w5500Server.handleRequest(handler);
    }

    if (deviceModel == DeviceModel::Rp2040Eth)
    {
        ch9120Server.handleRequest(handler);
    }
}