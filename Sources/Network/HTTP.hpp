//
// Created by antoine on 18/12/23.
//

#ifndef ECSPRESSP_HTTP_HPP
#define ECSPRESSP_HTTP_HPP

#include <asio.hpp>
#include "INetwork.hpp"

namespace express_cpp {

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
        void Disconnect();
        bool Connected() const;
    public:
        asio::ip::tcp::socket socket;
        std::vector<uint8_t> readBuffer;
        std::vector<uint8_t> sendBuffer;
    private:
        bool _is_connected;
    };

public:
    HTTP(uint16_t port = 8080, const std::string &address = "0.0.0.0");
    ~HTTP() = default;
    void Start(express_cpp::WriteOnlyQueue<Request> &requestQueue,
        ReadOnlyQueue<Response> &responseQueue
    ) override final;
private:
    void StartAccept(express_cpp::WriteOnlyQueue<Request> &requestQueue);
    void AcceptHandler(Client &client,
        express_cpp::WriteOnlyQueue<Request> &requestQueue
    );
    void StartReceive(Client &client,
        express_cpp::WriteOnlyQueue<Request> &requestQueue
    );
    void ReceiveHandler(Client &client,
        express_cpp::WriteOnlyQueue<Request> &requestQueue,
        const std::error_code error, std::size_t bytes_transfered
    );
    void Send(express_cpp::ReadOnlyQueue<Response> &responseQueue);
    static asio::ip::address_v4::bytes_type ParseAddress(
        const std::string &address
    );
    void DisconnectClients();

private:
    asio::io_context _io_context;
    asio::ip::tcp::acceptor _acceptor;
    std::vector<std::unique_ptr<Client>> _clients;
};
} // express_cpp

#endif //ECSPRESSP_HTTP_HPP
