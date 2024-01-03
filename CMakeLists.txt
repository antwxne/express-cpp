cmake_minimum_required(VERSION 3.16)

set(BIN_NAME express-cpp)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE "RELEASE" CACHE STRING "Sets release build by default")

if (WIN32)
    set(CMAKE_CXX_FLAGS "/MP /Wall /EHsc")
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        add_definitions("/DDEBUG")
    endif ()
else ()
    set(CMAKE_CXX_FLAGS "-Wall -Wextra")
    set(CMAKE_C_FLAGS "-Wall -Wextra")
    if (${CMAKE_BUILD_TYPE} STREQUAL "Debug")
        add_definitions("-DDEBUG")
    endif ()
endif ()


project(express-cpp)
include(lib/pico.cmake)
include(Sources/Sources.cmake)

set(MAIN Sources/Main.cpp

)
set(SRC ${PICO_SRC}
        ${SRC}
)

add_library(${BIN_NAME} ${SRC})
target_link_libraries(${BIN_NAME} PUBLIC asio picohttpparser)
add_executable(a.out ${MAIN} ${SRC})
target_link_libraries(a.out PRIVATE asio)

include(Tests/Tests.cmake)
