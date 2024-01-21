//
// Created by antoine on 23/12/23.
//

#ifndef ECSPRESSP_INETWORK_HPP
#define ECSPRESSP_INETWORK_HPP

#include "Queue/WriteOnlyQueue.hpp"
#include "Queue/ReadOnlyQueue.hpp"
#include "Network/HttpRequest.hpp"
#include "Network/HttpResponse.hpp"

namespace express_cpp {

struct HTTPContext {
    HTTPContext() = default;
    HTTPContext(const HTTPContext &other) = default;
    HTTPContext &operator=(const HTTPContext &other) = default;
    std::string remote_endpoint;
    u_int16_t port;
};

using Request = std::pair<HTTPContext, HTTPRequest>;
using Response = std::pair<HTTPContext, HTTPResponse>;

class INetwork {
public:
    /**
     * This method will be call when the server will start.
     * @param requestQueue will be filled with requests received by the server.
     * @param responseQueue will be consumed and send by the server.
     */
    virtual void Start(express_cpp::WriteOnlyQueue<Request> &requestQueue,
        ReadOnlyQueue<Response> &responseQueue
    ) = 0;
};
} // express_cpp

#endif //ECSPRESSP_INETWORK_HPP
