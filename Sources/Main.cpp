#include "ExpressCPPApp.hpp"
#include "Network/HTTP.hpp"

int main()
{
    express_cpp::Config config;
    config.appName = "TEST";
    config.port = 9090;
    express_cpp::ExpressCPPApp<express_cpp::HTTP> app(config);

    app.Router().Route("GET", "/",
        []([[maybe_unused]]const auto &req, express_cpp::HTTPResponse &res) {
            res.headers["Content-Type"] = "text/html";
            res.send("<h1>Hello World</h1>");
        });
    app.Router().Route("GET", "/plop",
        []([[maybe_unused]]const auto &req, express_cpp::HTTPResponse &res) {
            res.headers["Content-Type"] = "text/html";
            res.send("<h1>PLOP</h1>");
        });
    app.Start();
    return 0;
}
