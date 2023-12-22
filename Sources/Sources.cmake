include_directories(Sources)
set(TOOLS_SRC
        Sources/Debug/Debug.cpp
        Sources/Debug/Debug.hpp
        Sources/Exceptions/MyException.cpp
        Sources/Exceptions/MyException.hpp
        Sources/Queue/WriteOnlyQueue.hpp
        Sources/Queue/QueueImplem.cpp
        Sources/Queue/QueueImplem.hpp)

set(SRC
        ${TOOLS_SRC}
        Sources/Network/NetworkHandler.cpp
        Sources/Network/NetworkHandler.hpp
)