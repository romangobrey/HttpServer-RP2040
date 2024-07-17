#include "HttpRequest.h"
#include "HttpMethodType.h"
#include "HttpParser.h"

using namespace Rp2040;

HttpRequest HttpParser::GetHttpRequest(String rawRequest)
{
    HttpRequest request;
    request.methodType = GetMethodType(rawRequest);
    request.methodName = GetMethod(rawRequest);
    request.arguments = GetArgument(rawRequest);
    std::pair<String, String> protocol = GetProtocol(rawRequest);
    request.protocolName = protocol.first;
    request.protocolVersion = protocol.second;
    request.headers = GetHeaders(rawRequest);
    request.body = GetContent(rawRequest);
    return request;
}

HttpMethodType HttpParser::GetMethodType(String content)
{
    String firstRow = GetFirstRow(content);
    int firstSpaceIdx = firstRow.indexOf(" ");
    String methodStr = firstRow.substring(0, firstSpaceIdx);
    methodStr.toUpperCase();

    if (methodStr == "GET")
    {
        return HttpMethodType::GET;
    }
    else if (methodStr == "POST")
    {
        return HttpMethodType::POST;
    }
    else if (methodStr == "PUT")
    {
        return HttpMethodType::PUT;
    }
    else if (methodStr == "PATCH")
    {
        return HttpMethodType::PATCH;
    }
    else if (methodStr == "DELETE")
    {
        return HttpMethodType::DELETE;
    }
    else if (methodStr == "HEAD")
    {
        return HttpMethodType::HEAD;
    }
    else if (methodStr == "OPTIONS")
    {
        return HttpMethodType::OPTIONS;
    }

    return HttpMethodType::UNKNOWN;
}

String HttpParser::GetMethod(String content)
{
    String firstRow = GetFirstRow(content);
    int firstSpaceIdx = firstRow.indexOf(" /");
    int secondSpaceIdx = firstRow.indexOf(" ", firstSpaceIdx + 2);
    String methodArgStr = firstRow.substring(firstSpaceIdx + 2, secondSpaceIdx);
    int paramsStartIds = methodArgStr.indexOf("?");
    if (paramsStartIds < 0)
    {
        return methodArgStr;
    }
    else
    {
        return methodArgStr.substring(0, paramsStartIds);
    }
}

String HttpParser::GetRawMethodType(HttpMethodType method)
{
    switch (method)
    {
    case GET:
        return "GET";
    case POST:
        return "POST";
    case PUT:
        return "PUT";
    case PATCH:
        return "PATCH";
    case DELETE:
        return "DELETE";
    case HEAD:
        return "HEAD";
    case OPTIONS:
        return "OPTIONS";
    default:
        return "UNKNOWN";
    }
}

String HttpParser::GetArgument(String content)
{
    String firstRow = GetFirstRow(content);
    int firstSpaceIdx = firstRow.indexOf(" /");
    int secondSpaceIdx = firstRow.indexOf(" ", firstSpaceIdx + 2);
    String methodArgStr = firstRow.substring(firstSpaceIdx + 2, secondSpaceIdx + 1);
    int paramsStartIds = methodArgStr.indexOf("?");
    if (paramsStartIds < 0)
    {
        return "";
    }
    else
    {
        return methodArgStr.substring(paramsStartIds + 1);
    }
}

String HttpParser::GetContent(String content)
{
    String bodyDelimiter = "\r\n\r\n";
    int postContentStartIdx = content.indexOf(bodyDelimiter);
    String argStr = content.substring(postContentStartIdx + bodyDelimiter.length());
    return argStr;
}

#pragma region PrivateFunctions

String HttpParser::GetFirstRow(String content)
{
    int firstRowEnd = content.indexOf("\r\n");
    String firstRow = content.substring(0, firstRowEnd + 1);
    return firstRow;
}

std::pair<String, String> HttpParser::GetProtocol(String content)
{
    String firstRow = GetFirstRow(content);
    int whitespaceIdx = firstRow.lastIndexOf(' ');
    String protocolSubStr = firstRow.substring(whitespaceIdx);
    int delimeterIdx = protocolSubStr.indexOf('/');
    String protocolType = protocolSubStr.substring(0, delimeterIdx);
    String protocolName = protocolSubStr.substring(delimeterIdx + 1);

    return std::pair<String, String>(protocolName, protocolType);
}

std::map<String, String> HttpParser::GetHeaders(String content)
{
    String rowDelimiter = "\r\n";
    int firstRowEnd = content.indexOf(rowDelimiter);
    String bodyDelimiter = "\r\n\r\n";
    int postContentStartIdx = content.indexOf(bodyDelimiter);
    String headersStr = content.substring(firstRowEnd + rowDelimiter.length(), postContentStartIdx + bodyDelimiter.length());
    std::map<String, String> headers;

    int headerDelimiterIdx = headersStr.indexOf(rowDelimiter);
    while (headerDelimiterIdx > 0)
    {
        String headerRow = headersStr.substring(0, headerDelimiterIdx);
        int semicolonIdx = headerRow.indexOf(':');
        String name = headerRow.substring(0, semicolonIdx);
        String value = headerRow.substring(semicolonIdx + 2);
        headers[name] = value;

        headersStr = headersStr.substring(headerDelimiterIdx + rowDelimiter.length());
        headerDelimiterIdx = headersStr.indexOf(rowDelimiter);
    }

    return headers;
}

#pragma endregion PrivateFunctions
