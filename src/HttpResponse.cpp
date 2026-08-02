#include "HttpResponse.h"

using namespace Rp2040;

String HttpResponse::toString()
{
    const char *endLine = "\r\n";

    // --- Estimate total size first ---
    size_t estimatedSize = 0;

    // "HTTP/1.1 " + code (up to 3 digits, but be safe) + ' ' + codeDescription + endLine
    estimatedSize += 9;                     // "HTTP/1.1 "
    estimatedSize += 5;                     // room for code digits (e.g. "200", "404", "500")
    estimatedSize += 1;                     // ' '
    estimatedSize += codeDescription.length();
    estimatedSize += 2;                     // endLine

    // headers
    for (std::map<String, String>::iterator it = headers.begin(); it != headers.end(); ++it)
    {
        estimatedSize += it->first.length();
        estimatedSize += 2;                 // ": "
        estimatedSize += it->second.length();
        estimatedSize += 2;                 // endLine
    }

    estimatedSize += 2;                     // blank line before body
    estimatedSize += body.length();

    // --- Reserve once, then build ---
    String reply;
    reply.reserve(estimatedSize);

    reply = "HTTP/1.1 ";
    reply.concat(code);
    reply.concat(' ');
    reply.concat(codeDescription);
    reply.concat(endLine);

    for (std::map<String, String>::iterator it = headers.begin(); it != headers.end(); ++it)
    {
        reply.concat(it->first);
        reply.concat(": ");
        reply.concat(it->second);
        reply.concat(endLine);
    }
    reply.concat(endLine);
    reply.concat(body);

    return reply;
}