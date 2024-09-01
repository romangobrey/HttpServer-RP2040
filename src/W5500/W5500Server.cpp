#include "W5500/W5500Server.h"
#include "HttpParser.h"
#include "Utils.h"

String Rp2040::W5500Server::getRawRequest(EthernetClient client)
{
    if (client.connected() == 0)
    {
        Serial.println("client is not connected");
        return "";
    }

    if (client.available() == 0)
    {
        Serial.println("client is not available");
        return "";
    }

    String request;
    bool currentLineIsBlank = true;

    while (true)
    {
        char c = client.read();
        request.concat(c);

        if (c == '\n' && currentLineIsBlank)
        {
            while (client.available())
            {
                char c = client.read();
                request.concat(c);
            }
            break;
        }
        else if (c == '\n')
        {
            currentLineIsBlank = true;
        }
        else if (c != '\r')
        {
            currentLineIsBlank = false;
        }
    }
    return request;
}

void Rp2040::W5500Server::sendResponse(EthernetClient client, HttpResponse response)
{
    client.println(response.toString());
}

void Rp2040::W5500Server::init(UCHAR serverIp[4], UWORD port)
{
    server = std::make_shared<EthernetServer>(port);

    // byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
    byte mac[6];
    Utils::generateRp2040MacAddress(mac);

    IPAddress ip(serverIp);

    Ethernet.init(W5500_EVB_Pico_EthernetPIN);
    Ethernet.begin(mac, ip);

    server->begin();
}

void Rp2040::W5500Server::handleRequest(HttpResponse (*callback)(HttpRequest))
{
    EthernetClient client = server->available();
    if (!client)
    {
        return;
    }

    String rawRequest = getRawRequest(client);
    if (callback != NULL)
    {
        HttpRequest request = Rp2040::HttpParser::getHttpRequest(rawRequest);
        HttpResponse response = callback(request);
        sendResponse(client, response);

        delay(1);
        client.stop();
    }
}

void Rp2040::W5500Server::handleRequest(IHttpHandler *handler)
{
    EthernetClient client = server->available();
    if (!client)
    {
        return;
    }

    String rawRequest = getRawRequest(client);
    if (handler != NULL)
    {
        HttpRequest request = Rp2040::HttpParser::getHttpRequest(rawRequest);
        HttpResponse response = handler->handle(request);
        sendResponse(client, response);

        delay(1);
        client.stop();
    }
}