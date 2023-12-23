//
// Created by antoine on 18/12/23.
//

#include "NetworkHandler.hpp"
#include "Debug/Debug.hpp"

namespace ecspressp {
NetworkHandler::NetworkHandler()
    : _io_context(),
    _acceptor(_io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8080))
{
}

void NetworkHandler::Start()
{
    StartAccept();
    _io_context.run();
    auto a = 0;
}

void NetworkHandler::StartAccept()
{
    auto new_client = std::make_unique<Client>(_io_context);

    if (!new_client) {
        Debug::err("Cannot allocate memory for new client");
        asio::post(_io_context, std::bind(&NetworkHandler::StartAccept, this));
        return;
    }
    _acceptor.async_accept(new_client->socket,
        std::bind(&NetworkHandler::AcceptHandler, this, std::ref(*new_client)));
    _clients.push_back(std::move(new_client));
}

void NetworkHandler::AcceptHandler(NetworkHandler::Client &client)
{
    if (client.GetSocketFd() < 0) {
        Debug::err("Cannot connect with new client");
        return;
    }
    Debug::log("HTTP Client connected");
    StartReceive(client);
    StartAccept();
}

void NetworkHandler::StartReceive(NetworkHandler::Client &client)
{
    std::string delimiter = "\r\n\r\n";
    asio::async_read_until(client.socket, asio::dynamic_buffer(client.buffer),
        delimiter,
        std::bind(&NetworkHandler::ReceiveHandler, this, std::ref(client),
            std::placeholders::_1, std::placeholders::_2));
}

void NetworkHandler::ReceiveHandler(NetworkHandler::Client &client,
    const std::error_code error, std::size_t bytes_transfered
)
{
    if (error == asio::error::eof) {
        Debug::log("Client disconnected");
        return;
    }
    Debug::log(std::to_string(bytes_transfered) + " bytes received");
    std::string request;
    request.resize(client.buffer.size());
    std::memcpy(request.data(), client.buffer.data(), client.buffer.size());

    client.buffer.clear();
    StartReceive(client);
}

int NetworkHandler::Client::GetSocketFd()
{
    return socket.native_handle();
}

NetworkHandler::Client::Client(asio::io_context &ioContext) : socket(ioContext)
{
}
} // ecspressp
