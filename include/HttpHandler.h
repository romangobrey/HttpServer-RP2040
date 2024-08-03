#include "HttpRequest.h"
#include "HttpResponse.h"

class IHttpHandler
{
public:
    virtual HttpResponse handle(const HttpRequest &request) = 0;
};