# Express CPP

Express like HTTP web server library in C++.

## Requirements

* a C++ compiler that support C++ standard version >= 20
* cmake >= 3.16

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
    app.Router().Get("/",
        []([[maybe_unused]]const auto &req, express_cpp::HTTPResponse &res) {
            res.headers["Content-Type"] = "text/html";
            res.send("<h1>Hello World</h1>");
        });
    // Adding a folder where static files are located
    app.Router().UseStatic("./Public");
    // Run the app
    app.Start();
    return 0;
    }
```

## Integration with CMake

```cmake
cmake_minimum_required(VERSION 3.16)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
include(FetchContent)
Set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(express-cpp
        GIT_REPOSITORY https://github.com/antwxne/express-cpp.git
        GIT_TAG master
        GIT_PROGRESS TRUE
)
FetchContent_GetProperties(express-cpp)
if (NOT express-cpp_POPULATED)
    FetchContent_Populate(express-cpp)
endif ()
add_subdirectory(${express-cpp_SOURCE_DIR})
include_directories(${express-cpp_SOURCE_DIR}/Sources)
target_link_libraries(<target> PRIVATE express-cpp)
```
