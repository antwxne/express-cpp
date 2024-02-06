//
// Created by antoine on 06/02/24.
//

#ifndef EXPRESS_CPP_CONFIG_HPP
#define EXPRESS_CPP_CONFIG_HPP

#include <string>

namespace express_cpp {

struct Config {
    short port;
    std::string address;
    std::string appName;
    std::size_t threadsNumber;
    std::size_t maxRequestSize;

    Config()
    {
        port = 8080;
        address = "0.0.0.0";
        appName = "Express-CPP_APP";
        threadsNumber = 1;
        maxRequestSize = 3000;
    }
};
} // express_cpp

#endif //EXPRESS_CPP_CONFIG_HPP
