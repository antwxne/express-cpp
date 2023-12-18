include(FetchContent)

FetchContent_Declare(asio-cmake
        GIT_REPOSITORY https://github.com/chriskohlhoff/asio
        GIT_TAG        asio-1-29-0
)
FetchContent_MakeAvailable(asio-cmake)