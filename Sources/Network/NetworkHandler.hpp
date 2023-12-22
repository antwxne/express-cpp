//
// Created by antoine on 18/12/23.
//

#ifndef ECSPRESSP_NETWORKHANDLER_HPP
#define ECSPRESSP_NETWORKHANDLER_HPP

#include <asio.hpp>

namespace ecspressp {

class NetworkHandler {
private:
    class Client{

    };

public:
    NetworkHandler();
    ~NetworkHandler() = default;
    void Start();
private:
    void StartAccept();
    void AcceptHandler();
    void StartReceive();
    void ReceiveHandler();
    void Send();
private:
    asio::ip::tcp::acceptor _acceptor;
    asio::io_context _io_context;
    std::vector<Client> _clients;


};
} // ecspressp

#endif //ECSPRESSP_NETWORKHANDLER_HPP
