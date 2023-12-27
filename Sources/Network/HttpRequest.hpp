//
// Created by antoine on 23/12/23.
//

#ifndef ECSPRESSP_HTTPREQUEST_HPP
#define ECSPRESSP_HTTPREQUEST_HPP

#include <string>
#include <map>
#include <vector>

namespace ecspressp {

struct HTTPRequest {
    ~HTTPRequest() = default;
    std::string httpVersion;
    std::string method;
    std::string route;
    std::map<std::string, std::string> headers;
    std::vector<u_int8_t> body;
    HTTPRequest() = default;
    void operator<<(std::vector<u_int8_t> &rawRequest);
};
} // ecspressp

#endif //ECSPRESSP_HTTPREQUEST_HPP
