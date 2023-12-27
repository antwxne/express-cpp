//
// Created by antoine on 23/12/23.
//

#ifndef ECSPRESSP_HTTPRESPONSE_HPP
#define ECSPRESSP_HTTPRESPONSE_HPP

#include <string>
#include <map>
#include <vector>

namespace express_cpp {

class HTTPResponse {
public:
    HTTPResponse();
    HTTPResponse &send(const std::string &str);
    HTTPResponse &send(const std::vector<u_int8_t> &buffer);
    HTTPResponse &status(int code);
    HTTPResponse &status(int code, const std::string &reason);
public:
    std::string httpVersion;
    int statusCode;
    std::string statusText;
    std::map<std::string, std::string> headers;
    std::vector<u_int8_t> body;
    void operator>>(std::vector<u_int8_t> &outputBuffer) const;
};
} // escpressp

#endif //ECSPRESSP_HTTPRESPONSE_HPP
