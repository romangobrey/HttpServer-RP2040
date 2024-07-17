#pragma once

#include <arduino.h>
#include <map>

namespace Rp2040
{
    class HttpResponse
    {
    public:
        unsigned short code;
        String codeDescription;
        std::map<String, String> headers;
        String body;
        String toString();
    };
}
