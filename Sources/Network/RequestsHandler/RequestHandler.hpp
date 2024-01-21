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

namespace express_cpp {

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
    void Get(const std::string &route, RouteCallback &&callback
    );
    void Head(const std::string &route, RouteCallback &&callback
    );
    void Post(const std::string &route, RouteCallback &&callback
    );
    void Put(const std::string &route, RouteCallback &&callback
    );
    void Delete(const std::string &route, RouteCallback &&callback
    );
    void Connect(const std::string &route, RouteCallback &&callback
    );
    void Options(const std::string &route, RouteCallback &&callback
    );
    void Trace(const std::string &route, RouteCallback &&callback
    );
    void Patch(const std::string &route, RouteCallback &&callback
    );
    void UseStatic(const std::string &path);
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
    void GetStaticFile(const HTTPRequest &request, HTTPResponse &response);
    static void CheckStaticPath(const std::string &path);

private:
    std::vector<std::string> _staticPaths;
    Headers _globalHeaders;
    MethodsRegistry _methodsRegistry;
};
} // express_cpp

#endif //ECSPRESSP_REQUESTHANDLER_HPP
