#include "ECsPressPapp.hpp"
#include "Network/HTTP.hpp"

int main()
{
    ecspressp::eCsPressPAPP<ecspressp::HTTP> app;

    app.Router().Route("GET", "/",
        [](const auto &req, ecspressp::HTTPResponse &res) {
            res.headers["Content-Type"] = "text/html";
            res.send("<h1>Hello World</h1>");
        });
    app.Router().Route("GET", "/plop",
        [](const auto &req, ecspressp::HTTPResponse &res) {
            res.headers["Content-Type"] = "text/html";
            res.send("<h1>PLOP</h1>");
        });
    app.Start();
    return 0;
}
