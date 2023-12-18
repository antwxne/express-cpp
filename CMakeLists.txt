cmake_minimum_required(VERSION 3.27)

project(eCsPressP)

set(BIN_NAME PLOP)

include(Dependencies/FindASIO.cmake)
include(Dependencies/pico.cmake)

set(MAIN Sources/Main.cpp)
set(SRC ${PICO_SRC})

add_library(${BIN_NAME} ${MAIN} ${SRC})
target_link_libraries(${BIN_NAME} PRIVATE asio-cmake)

