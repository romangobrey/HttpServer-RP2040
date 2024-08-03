#include "CH9120/CH9120.h"
#include "CH9120/CH9120Server.h"
#include "DeviceModel.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "W5500/W5500Server.h"

namespace Rp2040
{
    class HttpServer
    {
    private:
        bool isInitialized;
        DeviceModel deviceModel;
        CH9120Server ch9120Server;
        W5500Server w5500Server;

        String getRawRequest();
        void sendResponse(HttpResponse response);

    public:
        HttpServer(DeviceModel device);
        void init(UCHAR serverIp[4], UCHAR gateway[4], UCHAR subnetMask[4], UWORD port = 80, UDOUBLE baudRate = 115200);
        void handleRequest(HttpResponse (*callback)(HttpRequest));
        void handleRequest(IHttpHandler *handler);
    };
}
