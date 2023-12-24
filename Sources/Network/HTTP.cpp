//
// Created by antoine on 18/12/23.
//

#include "HTTP.hpp"
#include "Debug/Debug.hpp"

namespace ecspressp {
HTTP::HTTP()
    : _io_context(),
    _acceptor(_io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8080))
{
}

void HTTP::Start(ecspressp::WriteOnlyQueue<HTTPRequest> &requestQueue,
    ReadOnlyQueue<HTTPResponse> &responseQueue
)
{
    StartAccept(requestQueue);
    _io_context.run();
}

void HTTP::StartAccept(ecspressp::WriteOnlyQueue<HTTPRequest> &requestQueue)
{
    auto new_client = std::make_unique<Client>(_io_context);

    if (!new_client) {
        Debug::err("Cannot allocate memory for new client");
        asio::post(_io_context,
            std::bind(&HTTP::StartAccept, this, std::ref(requestQueue)));
        return;
    }
    _acceptor.async_accept(new_client->socket,
        std::bind(&HTTP::AcceptHandler, this, std::ref(*new_client),
            std::ref(requestQueue)));
    _clients.push_back(std::move(new_client));
}

void HTTP::AcceptHandler(Client &client,
    ecspressp::WriteOnlyQueue<HTTPRequest> &requestQueue
)
{
    if (client.GetSocketFd() < 0) {
        Debug::err("Cannot connect with new client");
        return;
    }
    Debug::log("HTTP Client connected");
    StartReceive(client, requestQueue);
    StartAccept(requestQueue);
}

void HTTP::StartReceive(Client &client,
    ecspressp::WriteOnlyQueue<HTTPRequest> &requestQueue
)
{
    const std::string delimiter = "\r\n\r\n";
    asio::async_read_until(client.socket, asio::dynamic_buffer(client.buffer),
        delimiter, std::bind(&HTTP::ReceiveHandler, this, std::ref(client),
            std::ref(requestQueue), std::placeholders::_1,
            std::placeholders::_2));
}

void HTTP::ReceiveHandler(Client &client,
    ecspressp::WriteOnlyQueue<HTTPRequest> &requestQueue,
    const std::error_code error, std::size_t bytes_transfered
)
{
    if (error == asio::error::eof) {
        Debug::log("Client disconnected");
        return;
    }
    Debug::log(std::to_string(bytes_transfered) + " bytes received");
    HTTPRequest request;
    request << client.buffer;

    client.buffer.clear();
    StartReceive(client, requestQueue);
}

int HTTP::Client::GetSocketFd()
{
    return socket.native_handle();
}

HTTP::Client::Client(asio::io_context &ioContext) : socket(ioContext)
{
}
} // ecspressp
