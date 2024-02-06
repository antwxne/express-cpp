//
// Created by antoine on 06/02/24.
//

#ifndef EXPRESS_CPP_HTTPEXCEPTION_HPP
#define EXPRESS_CPP_HTTPEXCEPTION_HPP

#include <stdexcept>

namespace express_cpp {

class HTTPException : public std::runtime_error {
public:
    HTTPException(int status_code = 500,
        const std::string &message = "Internal Server Error"
    );
    int status_code;
    std::string message;
};
} // express_cpp

#endif //EXPRESS_CPP_HTTPEXCEPTION_HPP
