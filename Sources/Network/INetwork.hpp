//
// Created by antoine on 23/12/23.
//

#ifndef ECSPRESSP_INETWORK_HPP
#define ECSPRESSP_INETWORK_HPP

#include "Queue/WriteOnlyQueue.hpp"
#include "Queue/ReadOnlyQueue.hpp"
#include "Network/HttpRequest.hpp"
#include "Network/HttpResponse.hpp"

namespace ecspressp {

class INetwork {
public:
    virtual void Start(ecspressp::WriteOnlyQueue<HTTPRequest> &requestQueue,
        ReadOnlyQueue<HTTPResponse> &responseQueue
    ) = 0;
};
} // ecspressp

#endif //ECSPRESSP_INETWORK_HPP
