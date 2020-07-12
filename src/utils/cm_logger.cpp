#include <iostream>
#include "cm_logger.h"

namespace cm
{
    void Log(std::string message, LogLevel logLevel)
    {
        if (logLevel >= GLOBAL_LOG_LEVEL && !message.empty())
        {
            std::string level;
            
            switch (logLevel)
            {
            case LOG_NONE:
                break;
            case LOG_INFO:
                level = "INFO";
                break;
            case LOG_WARNING:
                level = "WARNING";
                break;
            case LOG_ERROR:
                level = "ERROR";
                break;
            }

            std::cout << level << " : " << message << std::endl;
        }
    }

} // namespace cm