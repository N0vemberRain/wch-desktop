#pragma once

#include <QByteArray>
#include <QDateTime>
#include <chrono>
#include <expected>
#include <optional>
#include <span>
#include <cstddef>

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

inline std::vector<std::byte> toBytes(const QByteArray& ba)
{
    const auto* ptr =
        reinterpret_cast<const std::byte*>(ba.constData());

    return {ptr, ptr + ba.size()};
}

inline QByteArray toQByteArray(std::span<const std::byte> bytes)
{
    return QByteArray(
        reinterpret_cast<const char*>(bytes.data()),
        static_cast<qsizetype>(bytes.size())
        );
}

inline QByteArrayView toQByteArrayView(std::span<const std::byte> bytes)
{
    return QByteArrayView(
        reinterpret_cast<const char*>(bytes.data()),
        static_cast<qsizetype>(bytes.size())
        );
}