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
Set(FETCHCONTENT_QUIET FALSE)
include(Deps/PicoHTTPParser.cmake)
include(Deps/Asio.cmake)
include(Sources/Sources.cmake)

include_directories(Sources)

set(SRC ${SRC}
        Sources/Config.cpp
        Sources/Config.hpp

)

add_library(${BIN_NAME} ${SRC})
target_link_libraries(${BIN_NAME} PUBLIC asio picohttpparser)

#add_executable(PLOP Main.cpp)
#target_link_libraries(PLOP ${BIN_NAME})
