#pragma once

#include "HttpRequest.h"
#include "HttpResponse.h"

namespace Rp2040
{
    class IHttpHandler
    {
    public:
        virtual HttpResponse handle(const HttpRequest &request) = 0;
    };
}