#include "CH9120.h"
#include "HttpRequest.h"
#include "HttpResponse.h"
#include "HttpHandler.h"

namespace Rp2040
{
    class CH9120Server
    {
    private:
        String getRawRequest();
        void sendResponse(HttpResponse response);

    public:
        void init(UCHAR serverIp[4], UWORD port = 80);
        void handleRequest(HttpResponse (*callback)(HttpRequest));
        void handleRequest(IHttpHandler *handler);
    };
}