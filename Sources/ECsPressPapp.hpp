//
// Created by antoine on 23/12/23.
//

#ifndef ECSPRESSP_ECSPRESSPAPP_HPP
#define ECSPRESSP_ECSPRESSPAPP_HPP

#include <thread>
#include <type_traits>

#include "Queue/QueueImplem.hpp"
#include "Network/RequestsHandler/RequestHandler.hpp"
#include "Network/INetwork.hpp"

namespace ecspressp {
template<typename Network>
class eCsPressPAPP {
public:
    eCsPressPAPP();
    void Start();
    RequestHandler &Router();

private:
    Network _networkHandler;
    RequestHandler _requestHandler;
    ecspressp::QueueImplem<ecspressp::Request> input_queue;
    ecspressp::QueueImplem<ecspressp::Response> output_queue;
};

template<typename Network>
RequestHandler &eCsPressPAPP<Network>::Router()
{
    return _requestHandler;
}

template<typename Network>
void eCsPressPAPP<Network>::Start()
{
    QueueImplem<Request> requestsQueue;
    QueueImplem<Response> responsesQueue;
    bool shouldStop = false;
    std::thread requests(
        std::bind(&RequestHandler::StartHandle, _requestHandler,
            std::ref(requestsQueue), std::ref(responsesQueue),
            std::ref(shouldStop)));
    _networkHandler.Start(requestsQueue, responsesQueue);
}

template<typename Network>
eCsPressPAPP<Network>::eCsPressPAPP()
{
}
}

#endif //ECSPRESSP_ECSPRESSPAPP_HPP
