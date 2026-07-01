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

std::chrono::system_clock::time_point fromQString(const QString& s) {
    const QDateTime dt = QDateTime::fromString(s, Qt::ISODate);

    if (!dt.isValid())
        return {};

    return std::chrono::sys_time<std::chrono::milliseconds>{
        std::chrono::milliseconds{dt.toMSecsSinceEpoch()}
    };
}

QString toQString(const std::chrono::system_clock::time_point& tp) {
    const auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
                        tp.time_since_epoch()).count();

    return QDateTime::fromMSecsSinceEpoch(ms, Qt::UTC)
        .toString(Qt::ISODateWithMs);
}