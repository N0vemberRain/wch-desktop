#pragma once

#include <string>

struct User
{
    User();

    bool operator<=>(const User&) const = default;

    std::string id;
    std::string name;
    std::string email;

};
