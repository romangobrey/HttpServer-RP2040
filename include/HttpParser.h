#pragma once

#include <arduino.h>
#include "HttpMethodType.h"
#include "HttpRequest.h"

namespace Rp2040
{
    class HttpParser
    {
    public:
        static HttpRequest GetHttpRequest(String rawRequest);
        static HttpMethodType GetMethodType(String content);
        static String GetRawMethodType(HttpMethodType type);

    private:
        static String GetMethod(String content);
        static String GetArgument(String content);
        static String GetContent(String content);
        static String GetFirstRow(String content);
        static std::pair<String, String> GetProtocol(String content);
        static std::map<String, String> GetHeaders(String content);
    };
}
