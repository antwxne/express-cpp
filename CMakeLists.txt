cmake_minimum_required(VERSION 3.27)

set(BIN_NAME ecspressp)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(eCsPressP)
find_package(asio CONFIG REQUIRED)
include(lib/pico.cmake)
include(Sources/Sources.cmake)

#set(MAIN Sources/Main.cpp)
set(SRC ${PICO_SRC}
        ${SRC}
)

add_library(${BIN_NAME} ${MAIN} ${SRC})
target_link_libraries(${BIN_NAME} PRIVATE asio::asio)

include(Tests/Tests.cmake)

