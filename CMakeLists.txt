cmake_minimum_required(VERSION 3.27)

set(BIN_NAME ecspressp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    set(CMAKE_CXX_FLAGS "/MP /Wall")
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        add_definitions("/DDEBUG")
    endif ()
else ()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
    set(CMAKE_CXX_FLAGS_Debug "${CMAKE_CXX_FLAGS} -g")
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        add_definitions("-DDEBUG")
    endif ()
endif ()


project(eCsPressP)
find_package(asio CONFIG REQUIRED)
include(lib/pico.cmake)
include(Sources/Sources.cmake)

set(MAIN Sources/Main.cpp)
set(SRC ${PICO_SRC}
        ${SRC}
)

add_library(${BIN_NAME} ${SRC})
target_link_libraries(${BIN_NAME} PRIVATE asio::asio)
add_executable(a.out ${MAIN} ${SRC})
target_link_libraries(a.out PRIVATE asio::asio)

include(Tests/Tests.cmake)
