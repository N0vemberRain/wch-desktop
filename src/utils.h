#pragma once

#include <QDateTime>
#include <chrono>
#include <expected>
#include <optional>

QDateTime toQDateTime(std::chrono::system_clock::time_point tp);
std::chrono::system_clock::time_point fromQDateTime(const QDateTime& dt);
std::chrono::system_clock::time_point fromQString(const QString& s);
QString toQString(const std::chrono::system_clock::time_point& tp);


template <typename T, typename E>
std::expected<T, E> to_expected(const std::optional<T>& opt, E error_value) {
    if (opt) {
        return *opt;
    }
    return std::unexpected(error_value);
}