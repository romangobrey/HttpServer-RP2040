#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpHandler.h"
#include <Ethernet.h>
#include <memory>

#define UCHAR unsigned char
#define UDOUBLE uint32_t
#define UWORD uint16_t

namespace Rp2040
{
    class W5500Server
    {
    private:
        const short W5500_EVB_Pico_EthernetPIN = 17;

        std::shared_ptr<EthernetServer> server;
        String getRawRequest(EthernetClient client);
        void sendResponse(EthernetClient client, HttpResponse response);

    public:
        void init(UCHAR serverIp[4], UWORD port = 80);
        void handleRequest(HttpResponse (*callback)(HttpRequest));
        void handleRequest(IHttpHandler *handler);
    };
}