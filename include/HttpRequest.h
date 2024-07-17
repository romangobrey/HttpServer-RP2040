#pragma once

#include <Arduino.h>
#include "HttpMethodType.h"
#include <map>

namespace Rp2040
{
    class HttpRequest
    {
    public:
        HttpMethodType methodType;
        String methodName;
        String arguments;
        String protocolName;    // HTTP or HTTPS
        String protocolVersion; // 1.0, 1.1
        std::map<String, String> headers;
        String body;
    };
}