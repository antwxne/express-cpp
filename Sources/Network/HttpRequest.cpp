//
// Created by antoine on 23/12/23.
//

#include <cstring>

#include "HttpRequest.hpp"
#include "picohttpparser.h"

namespace ecspressp {
void HTTPRequest::operator<<(std::vector<u_int8_t> &rawRequest
)
{
    std::string buffer;
    int minorVersion;
    const char *requestMethod;
    size_t methodLen;
    const char *path;
    size_t pathLen;
    struct phr_header requestHeaders[100];
    size_t requestHeadersLen = sizeof(requestHeaders) / sizeof(*requestHeaders);
    int contentLength;

    buffer.resize(rawRequest.size());
    std::memcpy(buffer.data(), rawRequest.data(), rawRequest.size());

    phr_parse_request(buffer.data(), rawRequest.size(), &requestMethod,
        &methodLen, &path, &pathLen, &minorVersion, requestHeaders,
        &requestHeadersLen, 0);
    httpVersion = "1." + std::to_string(minorVersion);
    method = requestMethod;
    method.resize(methodLen);
    route = path;
    route.resize(pathLen);
    for (size_t i = 0; i < requestHeadersLen; ++i) {
        std::string name = requestHeaders[i].name;
        std::string value = requestHeaders[i].value;
        name.resize(requestHeaders[i].name_len);
        value.resize(requestHeaders[i].value_len);
        headers.insert({name, value});
    }
    contentLength = std::atoi(headers["Content-Length"].data());
    body.resize(contentLength);
    std::memcpy(body.data(), &*(buffer.end() - contentLength), contentLength);
}
} // ecspressp
