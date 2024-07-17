#include "CH9120.h"
#include "HttpRequest.h"
#include "HttpResponse.h"

namespace Rp2040
{
    class IHttpHandler
    {
    public:
        void handle(HttpRequest &request);
        ~IHttpHandler() {}
    };

    class HttpServer
    {
    private:
        bool isInitialized;

        String getRawRequest();
        void sendResponse(HttpResponse response);

    public:
        void init(UCHAR serverIp[4], UCHAR gateway[4], UCHAR subnetMask[4], UWORD port = 80, UDOUBLE baudRate = 115200);
        void handleRequest(HttpResponse (*callback)(HttpRequest));
        void handleRequestWithHandler(IHttpHandler *handler);
    };
}
