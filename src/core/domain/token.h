#pragma once

#include <string>
#include <chrono>

struct Token {
    std::string value;
    std::string user_id;
    std::chrono::system_clock::time_point expires_at;

    bool operator<=>(const Token&) const = default;
};