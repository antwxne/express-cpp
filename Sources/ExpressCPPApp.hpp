//
// Created by antoine on 23/12/23.
//

#ifndef ECSPRESSP_ECSPRESSPAPP_HPP
#define ECSPRESSP_ECSPRESSPAPP_HPP

#include <thread>
#include <type_traits>

#include "Queue/QueueImplem.hpp"
#include "Network/RequestsHandler/RequestHandler.hpp"
#include "Network/HTTP.hpp"

namespace express_cpp {
struct Config {
    Config()
    {
        port = 8080;
        address = "0.0.0.0";
        appName = "Express-CPP_APP";
        threadsNumber = 1;
    }

    short port;
    std::string address;
    std::string appName;
    std::size_t threadsNumber;
};

template<typename Network>
class ExpressCPPApp {
    static_assert(std::is_base_of<INetwork, Network>());
public:
    explicit ExpressCPPApp(const Config &config);
    explicit ExpressCPPApp() = default;
    void Start();
    RequestHandler &Router();

private:
    Network _networkHandler;
    RequestHandler _requestHandler;
    express_cpp::QueueImplem<express_cpp::Request> _input_queue;
    express_cpp::QueueImplem<express_cpp::Response> _output_queue;
    std::size_t _threadsNumber;
};

template<typename Network>
ExpressCPPApp<Network>::ExpressCPPApp(const Config &config): _networkHandler(
    config.port, config.address), _requestHandler(), _input_queue(),
    _output_queue(), _threadsNumber(config.threadsNumber)
{
    _requestHandler.SetGlobalHeaders({{"User-Agent", config.appName}});
}

template<typename Network>
RequestHandler &ExpressCPPApp<Network>::Router()
{
    return _requestHandler;
}

template<typename Network>
void ExpressCPPApp<Network>::Start()
{
    QueueImplem<Request> requestsQueue;
    QueueImplem<Response> responsesQueue;
    bool shouldStop = false;
    std::vector<std::thread> threads;
    for (size_t i = 0; i < _threadsNumber; ++i) {
        threads.emplace_back(
            std::bind(&RequestHandler::StartHandle, _requestHandler,
                std::ref(requestsQueue), std::ref(responsesQueue),
                std::ref(shouldStop)));
    }
    _networkHandler.Start(requestsQueue, responsesQueue);
    std::for_each(threads.begin(), threads.end(), [](std::thread &thread) {
        thread.join();
    });
}
}

#endif //ECSPRESSP_ECSPRESSPAPP_HPP
