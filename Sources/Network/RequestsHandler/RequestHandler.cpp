//
// Created by antoine on 27/12/23.
//

#include <stdexcept>
#include <format>

#include "RequestHandler.hpp"
#include "Debug/Debug.hpp"

namespace express_cpp {
void RequestHandler::StartHandle(ReadOnlyQueue<Request> &requestQueue,
    WriteOnlyQueue<Response> &responseQueue, bool &shouldStop
)
{
    while (!shouldStop) {
        HandleRequests(requestQueue, responseQueue);
    }
}

void RequestHandler::Route(const std::string &method, const std::string &route,
    RouteCallback &&callback
)
{
    _methodsRegistry[method][route] = callback;
}

void RequestHandler::HandleRequests(ReadOnlyQueue<Request> &requestQueue,
    WriteOnlyQueue<Response> &responseQueue
)
{
    while (requestQueue.IsEmpty());
    const auto &&maybeRequest = requestQueue.Pop();
    if (!maybeRequest) {
        return;
    }
    Request request = maybeRequest.value();
    HTTPResponse newResponse;
    HTTPContext client_context = request.first;

    newResponse.headers = _globalHeaders;
    try {
        _methodsRegistry.at(request.second.method).at(request.second.route)(
            request.second, newResponse);
    } catch (std::out_of_range &_) {
        newResponse.status(404, "Not Found");
    }
    Debug::log(std::format("{}:{} {} {} {}", request.first.remote_endpoint,
        request.first.port, request.second.method, request.second.route,
        newResponse.statusCode));
    SetHeadersToResponse(newResponse);
    responseQueue.Push(
        Response(std::move(client_context), std::move(newResponse)));
}

void RequestHandler::SetHeadersToResponse(HTTPResponse &response)
{
    for (const auto &[name, value]: _globalHeaders) {
        if (!response.headers.contains(
            name)) { // to not override header set by the user
            response.headers[name] = value;
        }
    }
    response.headers["Content-Length"] = std::to_string(response.body.size());
}
} // express_cpp
