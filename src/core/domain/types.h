#pragma once

#include <string>
#include <vector>
#include <cstddef>

using UserID = std::string;
using ChatID = std::string;
using MessageID = std::string;

struct AvatarData {
    using BuffBytes = std::vector<std::byte>;

    bool operator<=>(const AvatarData&) const = default;

    UserID user_id;
    BuffBytes img_data;
    std::string mime_type;
};
