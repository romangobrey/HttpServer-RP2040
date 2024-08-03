#include "W5500/W5500Server.h"
#include <HttpParser.h>

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
         break;
      }
      if (c == '\n')
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

void Rp2040::W5500Server::init(UCHAR serverIp[4], UCHAR gateway[4], UCHAR subnetMask[4], UWORD port, UDOUBLE baudRate)
{
   server = std::make_shared<EthernetServer>(port);
   Ethernet.init(W5500_EVB_Pico_EthernetPIN);

   byte mac[] = {0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED};
   IPAddress ip(serverIp[0], serverIp[1], serverIp[2], serverIp[3]);
   IPAddress gateWay(gateway[0], gateway[1], gateway[2], gateway[3]);

   IPAddress subnet(subnetMask[0], subnetMask[1], subnetMask[2], subnetMask[3]);
   Ethernet.setGatewayIP(ip);
   Ethernet.setSubnetMask(subnet);
   Ethernet.begin(mac, ip);

   server->begin();
   // set boud rate?
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
      HttpRequest request = Rp2040::HttpParser::GetHttpRequest(rawRequest);
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
      HttpRequest request = Rp2040::HttpParser::GetHttpRequest(rawRequest);
      HttpResponse response = handler->handle(request);
      sendResponse(client, response);

      delay(1);
      client.stop();
   }
}