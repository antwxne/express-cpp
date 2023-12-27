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
        void operator>>(HTTPContext &context) const;
        bool operator==(const HTTPContext &context) const;
        void operator<<(const HTTPResponse &response);
    public:
        asio::ip::tcp::socket socket;
        std::vector<uint8_t> readBuffer;
        std::vector<uint8_t> sendBuffer;
    };

public:
    HTTP();
    ~HTTP() = default;
    void Start(ecspressp::WriteOnlyQueue<Request> &requestQueue,
        ReadOnlyQueue<Response> &responseQueue
    ) override final;
private:
    void StartAccept(ecspressp::WriteOnlyQueue<Request> &requestQueue);
    void AcceptHandler(Client &client,
        ecspressp::WriteOnlyQueue<Request> &requestQueue
    );
    void StartReceive(Client &client,
        ecspressp::WriteOnlyQueue<Request> &requestQueue
    );
    void ReceiveHandler(Client &client,
        ecspressp::WriteOnlyQueue<Request> &requestQueue,
        const std::error_code error, std::size_t bytes_transfered
    );
    void Send(ecspressp::ReadOnlyQueue<Response> &responseQueue);
private:
    asio::io_context _io_context;
    asio::ip::tcp::acceptor _acceptor;
    std::vector<std::unique_ptr<Client>> _clients;
};
} // ecspressp

#endif //ECSPRESSP_HTTP_HPP
