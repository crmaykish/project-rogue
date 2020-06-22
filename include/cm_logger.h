#ifndef CM_LOGGER_H
#define CM_LOGGER_H

#include <string>

namespace cm
{
    enum LogLevel
    {
        LOG_INFO,
        LOG_WARNING,
        LOG_ERROR,
        LOG_NONE
    };

    const LogLevel GLOBAL_LOG_LEVEL = LOG_INFO;

    void Log(std::string message, LogLevel logLevel = LOG_INFO);

} // namespace cm

#endif // CM_LOGGER_H
