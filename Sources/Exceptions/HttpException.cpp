//
// Created by antoine on 06/02/24.
//

#include "HttpException.hpp"

namespace express_cpp {
HTTPException::HTTPException(int new_status_code,
    const std::string &new_message
) : std::runtime_error(message), status_code(new_status_code),
    message(new_message)
{
}
} // express_cpp
