//
// Created by antoine on 27/12/23.
//

#ifndef ECSPRESSP_REQUESTHANDLER_HPP
#define ECSPRESSP_REQUESTHANDLER_HPP

#include <string>
#include <unordered_map>
#include <functional>
#include <variant>

#include "Network/INetwork.hpp"

namespace ecspressp {

using RouteCallback = std::function<void(const HTTPRequest &, HTTPResponse &
)>;
using RoutesRegistry = std::unordered_map<std::string, RouteCallback>;
using MethodsRegistry = std::unordered_map<std::string, RoutesRegistry>;

using Headers = std::map<std::string, std::string>;

class RequestHandler {
public:
    void Route(const std::string &method, const std::string &route,
        RouteCallback &&callback
    );
    void StartHandle(ReadOnlyQueue<Request> &requestQueue,
        WriteOnlyQueue<Response> &responseQueue, bool &shouldStop
    );

    void SetGlobalHeaders(Headers &&headers)
    {
        _globalHeaders = headers;
    };

private:
    void HandleRequests(ReadOnlyQueue<Request> &requestQueue,
        WriteOnlyQueue<Response> &responseQueue
    );
    void SetHeadersToResponse(HTTPResponse &response);

private:
    Headers _globalHeaders;
    MethodsRegistry _methodsRegistry;
};
} // ecspressp

#endif //ECSPRESSP_REQUESTHANDLER_HPP
