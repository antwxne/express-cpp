include(FetchContent)
FetchContent_Declare(asio
        GIT_REPOSITORY git@github.com:chriskohlhoff/asio.git
        GIT_TAG master
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
)
FetchContent_GetProperties(asio)
if (NOT asio_POPULATED)
    FetchContent_Populate(asio)
endif ()
FetchContent_Declare(sfml
        GIT_REPOSITORY git@github.com:SFML/SFML.git
        GIT_TAG master
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
)
FetchContent_GetProperties(sfml)
if (NOT sfml_POPULATED)
    FetchContent_Populate(sfml)
endif ()

add_library(asio INTERFACE)
target_include_directories(asio INTERFACE ${asio_SOURCE_DIR}/asio/include)
find_package(Threads)
target_link_libraries(asio INTERFACE Threads::Threads)

set(PICO_SRC ${CMAKE_SOURCE_DIR}/lib/picohttpparser/picohttpparser.c)
include_directories(${CMAKE_SOURCE_DIR}/lib/picohttpparser)
include_directories(${CMAKE_SOURCE_DIR}/lib/picojson)
