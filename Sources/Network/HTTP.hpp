//
// Created by antoine on 18/12/23.
//

#ifndef ECSPRESSP_HTTP_HPP
#define ECSPRESSP_HTTP_HPP

#include <asio.hpp>
#include "INetwork.hpp"

namespace ecspressp {

class HTTP : public INetwork {
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
    HTTP();
    ~HTTP() = default;
    void Start(ecspressp::WriteOnlyQueue<HTTPRequest> &requestQueue,
        ReadOnlyQueue<HTTPResponse> &responseQueue
    ) override final;
private:
    void StartAccept(ecspressp::WriteOnlyQueue<HTTPRequest> &requestQueue);
    void AcceptHandler(Client &client,
        ecspressp::WriteOnlyQueue<HTTPRequest> &requestQueue
    );
    void StartReceive(Client &client,
        ecspressp::WriteOnlyQueue<HTTPRequest> &requestQueue
    );
    void ReceiveHandler(Client &client,
        ecspressp::WriteOnlyQueue<HTTPRequest> &requestQueue,
        const std::error_code error, std::size_t bytes_transfered
    );
    //    void Send();
private:
    asio::io_context _io_context;
    asio::ip::tcp::acceptor _acceptor;
    std::vector<std::unique_ptr<Client>> _clients;
};
} // ecspressp

#endif //ECSPRESSP_HTTP_HPP
