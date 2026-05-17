#include "utils.h"


QDateTime toQDateTime(std::chrono::system_clock::time_point tp) {
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        tp.time_since_epoch());

    return QDateTime::fromMSecsSinceEpoch(ms.count(), Qt::UTC);
}

std::chrono::system_clock::time_point fromQDateTime(const QDateTime& dt) {
    auto ms = dt.toMSecsSinceEpoch();

    return std::chrono::system_clock::time_point{
        std::chrono::milliseconds{ms}
    };
}
