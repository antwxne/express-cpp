//
// Created by antoine on 27/12/23.
//

#include <stdexcept>
#include <format>
#include <fstream>

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
    const auto maybeRequest = requestQueue.Pop();
    if (!maybeRequest) {
        return;
    }
    Request request = maybeRequest.value();
    HTTPResponse newResponse;
    HTTPContext client_context = request.first;

    newResponse.headers = _globalHeaders;
    try {

        try {
            GetStaticFile(request.second, newResponse);
        } catch (std::runtime_error &e) {
            _methodsRegistry.at(request.second.method).at(request.second.route)(
                request.second, newResponse);
        }
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

void RequestHandler::Get(const std::string &route, RouteCallback &&callback)
{
    Route("GET", route, std::move(callback));
}

void RequestHandler::Head(const std::string &route, RouteCallback &&callback)
{
    Route("HEAD", route, std::move(callback));
}

void RequestHandler::Post(const std::string &route, RouteCallback &&callback)
{
    Route("POST", route, std::move(callback));
}

void RequestHandler::Put(const std::string &route, RouteCallback &&callback)
{
    Route("PUT", route, std::move(callback));
}

void RequestHandler::Delete(const std::string &route, RouteCallback &&callback)
{
    Route("DELETE", route, std::move(callback));
}

void RequestHandler::Connect(const std::string &route, RouteCallback &&callback)
{
    Route("CONNECT", route, std::move(callback));
}

void RequestHandler::Options(const std::string &route, RouteCallback &&callback)
{
    Route("OPTIONS", route, std::move(callback));
}

void RequestHandler::Trace(const std::string &route, RouteCallback &&callback)
{
    Route("TRACE", route, std::move(callback));
}

void RequestHandler::Patch(const std::string &route, RouteCallback &&callback)
{
    Route("PATCH", route, std::move(callback));
}

void RequestHandler::UseStatic(const std::string &path)
{
    _staticPaths.push_back(path);
}

void RequestHandler::GetStaticFile(const HTTPRequest &request,
    HTTPResponse &response
)
{
    CheckStaticPath(request.route);
    for (const auto &staticFolder: _staticPaths) {
        std::string path = std::format("{}/{}", staticFolder, request.route);
        std::ifstream file(path, std::ios::binary);
        if (file.is_open()) {
            std::vector<u_int8_t> data((std::istreambuf_iterator<char>(file)),
                std::istreambuf_iterator<char>());
            response.body = data;
            file.close();
            return;
        }
    }
    throw std::runtime_error(
        std::format("file: {} not found in the server", request.route));
}

void RequestHandler::CheckStaticPath(const std::string &path)
{
    if (path.find("..") == std::string::npos) {
        throw (std::runtime_error(
            std::format("Error: {}. Directory traversal detected.", path)));
    }
}
} // express_cpp
