//
// Created by antoine on 18/12/23.
//

#ifndef ECSPRESSP_NETWORKHANDLER_HPP
#define ECSPRESSP_NETWORKHANDLER_HPP

#include <asio.hpp>

namespace ecspressp {

class NetworkHandler {
private:
    class Client {
    public:
        Client(asio::io_context &ioContext);
        ~Client() = default;
        int GetSocketFd();
    public:
        asio::ip::tcp::socket socket;
        std::vector<uint8_t> buffer;
    };

public:
    NetworkHandler();
    ~NetworkHandler() = default;
    void Start();
private:
    void StartAccept();
    void AcceptHandler(Client &client);
    void StartReceive(Client &client);
    void ReceiveHandler(Client &client, const std::error_code error,
        std::size_t bytes_transfered
    );
    //    void Send();
private:
    asio::io_context _io_context;
    asio::ip::tcp::acceptor _acceptor;
    std::vector<std::unique_ptr<Client>> _clients;
};
} // ecspressp

#endif //ECSPRESSP_NETWORKHANDLER_HPP
