#pragma once

#include <QDateTime>
#include <chrono>

QDateTime toQDateTime(std::chrono::system_clock::time_point tp);
std::chrono::system_clock::time_point fromQDateTime(const QDateTime& dt);
std::chrono::system_clock::time_point fromQString(const QString& s);
QString toQString(const std::chrono::system_clock::time_point& tp);