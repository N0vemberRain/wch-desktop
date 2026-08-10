#pragma once

#include <string>

struct UserSummary {
    std::string id{};
    std::string name{};
    std::string email{};
    std::string avatar_key{};

    bool operator<=>(const UserSummary&) const = default;
};
