#ifndef NEWNEW_LOGGER_H
#define NEWNEW_LOGGER_H

#include <cstdarg>
#include <cstdio>
#include <chrono>
#include <string>

class Logger {
public:
    Logger(std::string className);
    void logDebug(const char* format, ...);
    void logError(const char* format, ...);
    void logDebugWithPrepend(std::string prepend, const char* format, va_list args);
    void logErrorWithPrepend(std::string prepend, const char* format, va_list args);

    static bool shouldPrintDebug;
    static bool shouldPrintError;
    static bool shouldOnlyPrintSpecifiedClasses;
    static std::string classNamesToPrint[];

private:
    enum LogLevel {
        ERROR,
        DEBUG,
        INFO
    };

    void log(LogLevel logLevel, bool printPrepend, std::string prepend, const char* format, va_list args);
    static bool shouldPrintForClass(std::string className);

    std::string className;
};


#endif //NEWNEW_LOGGER_H
