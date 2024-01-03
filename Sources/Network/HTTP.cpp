//
// Created by antoine on 18/12/23.
//

#include <format>

#include "HTTP.hpp"
#include "Debug/Debug.hpp"

namespace express_cpp {
HTTP::HTTP(uint16_t port, const std::string &address)
    : _io_context(), _acceptor(_io_context,
    asio::ip::tcp::endpoint(asio::ip::address_v4(ParseAddress(address)), port))
{
}

void HTTP::Start(express_cpp::WriteOnlyQueue<Request> &requestQueue,
    ReadOnlyQueue<Response> &responseQueue
)
{
    StartAccept(requestQueue);
    _io_context.post(std::bind(&HTTP::Send, this, std::ref(responseQueue)));
    Debug::log(std::format("Server listening on http://{}:{}",
        _acceptor.local_endpoint().address().to_string(),
        _acceptor.local_endpoint().port()));
    _io_context.run();
}

void HTTP::StartAccept(express_cpp::WriteOnlyQueue<Request> &requestQueue)
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
    express_cpp::WriteOnlyQueue<Request> &requestQueue
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
    express_cpp::WriteOnlyQueue<Request> &requestQueue
)
{
    const std::string delimiter = "\r\n\r\n";
    // TODO a changer par un async read sinon overflow si on envoie n'importe quoi
    asio::async_read_until(client.socket,
        asio::dynamic_buffer(client.readBuffer), delimiter,
        std::bind(&HTTP::ReceiveHandler, this, std::ref(client),
            std::ref(requestQueue), std::placeholders::_1,
            std::placeholders::_2));
}

void HTTP::ReceiveHandler(Client &client,
    express_cpp::WriteOnlyQueue<Request> &requestQueue,
    const std::error_code error, std::size_t bytes_transfered
)
{
    if (error == asio::error::eof) {
        Debug::log("Client disconnected");
        return;
    }
    Debug::log(std::to_string(bytes_transfered) + " bytes received");
    HTTPRequest httpRequest;
    HTTPContext context;

    httpRequest << client.readBuffer;
    client >> context;
    requestQueue.Push(Request(context, httpRequest));
    client.readBuffer.clear();
    StartReceive(client, requestQueue);
}

void HTTP::Send(ReadOnlyQueue<Response> &responseQueue)
{
    while (!responseQueue.IsEmpty()) {
        // this part will be so much prettier with pattern matching...
        const auto maybe_response = responseQueue.Pop();
        if (!maybe_response) {
            continue;
        }
        const auto &response = maybe_response.value();
        const auto &clientToSend = std::find_if(_clients.begin(),
            _clients.end(), [&](const std::unique_ptr<Client> &client) -> bool {
                return *client == response.first;
            });
        if (clientToSend == _clients.cend()) {
            continue;
        }
        **clientToSend << response.second;
    }

    _io_context.post(std::bind(&HTTP::Send, this, std::ref(responseQueue)));
}

asio::ip::address_v4::bytes_type HTTP::ParseAddress(const std::string &address)
{
    // from https://stackoverflow.com/a/5328190
    std::stringstream s(address);
    int a, b, c, d; //to store the 4 ints
    char ch; //to temporarily store the '.'
    s >> a >> ch >> b >> ch >> c >> ch >> d;
    return asio::ip::address_v4::bytes_type(
        {static_cast<uint8_t>(a), static_cast<uint8_t>(b),
            static_cast<uint8_t>(c), static_cast<uint8_t>(d)});
}

int HTTP::Client::GetSocketFd()
{
    return socket.native_handle();
}

HTTP::Client::Client(asio::io_context &ioContext) : socket(ioContext)
{
}

void HTTP::Client::operator>>(HTTPContext &context) const
{
    context.remote_endpoint = socket.remote_endpoint().address().to_string();
    context.port = socket.remote_endpoint().port();
}

bool HTTP::Client::operator==(const HTTPContext &context) const
{
    return context.remote_endpoint ==
        socket.remote_endpoint().address().to_string() &&
        context.port == socket.remote_endpoint().port();
}

void HTTP::Client::operator<<(const HTTPResponse &response)
{
    response >> sendBuffer;
    socket.async_send(asio::buffer(sendBuffer),
        [&]([[maybe_unused]]const asio::error_code &error,
            const std::size_t bytes_transfered
        ) {
            asio::ip::tcp::endpoint client_endpoint = socket.remote_endpoint();
            Debug::log(std::format("{} bytes sent to {}:{}", bytes_transfered,
                client_endpoint.address().to_string(), client_endpoint.port()));
        });
}
} // express_cpp
