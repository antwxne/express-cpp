# Express CPP

Express like HTTP web server library in C++.

## Requirements

* a C++ compiler that support C++ standard version >= 20
* cmake >= 3.16
* VCPKG and set the environnement
  variable `CMAKE_TOOLCHAIN_FILE=<path to the vcpkg folder>/scripts/buildsystems/vcpkg.cmake`

## Build

```shell
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
cmake --build build --target express-cpp
```

> if you want some debug information change the build type to `Debug`

## Example

main.cpp:

```cpp
#include "ExpressCPPApp.hpp"
#include "Network/HTTP.hpp"

int main()
{
    // Configure the app
    express_cpp::Config config;
    config.appName = "MyApp";
    config.port = 9090;
    // Create the app with HTTP handler
    express_cpp::ExpressCPPApp<express_cpp::HTTP> app(config);
    // Create a GET request handler on the / route
    app.Router().get("/",
        []([[maybe_unused]]const auto &req, express_cpp::HTTPResponse &res) {
            res.headers["Content-Type"] = "text/html";
            res.send("<h1>Hello World</h1>");
        });
    // Adding a folder where static files are located
    app.Router().UseStatic("./Public");
    // Run the app
    app.Start();
    return 0;
```
