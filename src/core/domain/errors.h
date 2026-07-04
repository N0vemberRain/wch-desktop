#pragma once

#include <string>

enum class ErrorCode {
    Network,
    Timeout,
    Unauthorized,
    Forbidden,
    NotFound,
    ServerError,
    InvalidResponse,
    Unknown
};

struct Error {
    Error() {}
    explicit Error(ErrorCode code, std::string&& msg)
        : code{code}, msg{msg}
    {

    }

    bool operator<=>(const Error& e) const = default;

    ErrorCode code;
    std::string msg;
};
