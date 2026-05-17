#ifndef UTILS_H
#define UTILS_H

#include <QDateTime>
#include <chrono>

QDateTime toQDateTime(std::chrono::system_clock::time_point tp);
std::chrono::system_clock::time_point fromQDateTime(const QDateTime& dt);

#endif // UTILS_H
