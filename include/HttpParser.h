#pragma once

#include <arduino.h>
#include "HttpMethodType.h"
#include "HttpRequest.h"

namespace Rp2040
{
    class HttpParser
    {
    public:
        static HttpRequest getHttpRequest(String rawRequest);
        static HttpMethodType getMethodType(String content);
        static String getRawMethodType(HttpMethodType type);

    private:
        static String getMethod(String content);
        static String getArgument(String content);
        static String getContent(String content);
        static String getFirstRow(String content);
        static std::pair<String, String> getProtocol(String content);
        static std::map<String, String> getHeaders(String content);
    };
}
