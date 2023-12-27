//
// Created by antoine on 23/12/23.
//

#include <cstring>
#include <format>
#include <unordered_map>

#include <string>

#include "HttpResponse.hpp"

namespace ecspressp {
void HTTPResponse::operator>>(std::vector<u_int8_t> &outputBuffer) const
{
    std::string dest = std::format("{} {} {}\r\n", httpVersion, statusCode,
        statusText);
    for (const auto &[name, value]: headers) {
        dest += std::format("{}: {}\r\n", name, value);
    }
    dest += "\r\n";
    outputBuffer.resize(dest.length() + body.size());
    std::memcpy(outputBuffer.data(), dest.data(), dest.length());
    std::memcpy(&outputBuffer.at(dest.length() - 1), body.data(), body.size());
}

HTTPResponse &HTTPResponse::send(const std::string &str)
{
    const std::size_t endOfBody = body.size();

    body.resize(body.size() + str.length());
    std::memcpy(&body.at(endOfBody), str.data(), str.length());
    return *this;
}

HTTPResponse &HTTPResponse::send(const std::vector<u_int8_t> &buffer)
{
    const std::size_t endOfBody = body.size();

    body.resize(body.size() + buffer.size());
    std::memcpy(&body.at(endOfBody), buffer.data(), buffer.size());
    return *this;
}

HTTPResponse &HTTPResponse::status(int code)
{
    statusCode = code;
    statusText = "OK";
    return *this;
}

HTTPResponse &HTTPResponse::status(int code, const std::string &reason
)
{
    statusCode = code;
    statusText = reason;
    return *this;
}

HTTPResponse::HTTPResponse() : httpVersion("HTTP/1.1"), statusCode(200),
    statusText("OK"), headers(), body()
{
}
} // escpressp
