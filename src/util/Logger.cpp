#include "../../includes/util/Logger.h"

bool Logger::shouldPrintDebug = true;
bool Logger::shouldPrintError = true;
bool Logger::shouldOnlyPrintSpecifiedClasses = true;
std::string Logger::classNamesToPrint[] = {"Game", "XmlManager", "ViewManager"};

Logger::Logger(std::string className) {
    this->className = className;
}

void Logger::logDebug(const char* format, ...) {
    if(shouldPrintDebug) {
        va_list args;
        va_start(args, format);
        log(LogLevel::DEBUG, false, "", format, args);
        va_end(args);
    }
}

void Logger::logError(const char* format, ...) {
    if(shouldPrintError) {
        va_list args;
        va_start(args, format);
        log(LogLevel::ERROR, false, "", format, args);
        va_end(args);
    }
}

void Logger::logDebugWithPrepend(std::string prepend, const char* format, va_list args) {
    if(shouldPrintDebug) {
        log(LogLevel::DEBUG, true, prepend, format, args);
    }
}

void Logger::logErrorWithPrepend(std::string prepend, const char* format, va_list args) {
    if(shouldPrintError) {
        log(LogLevel::ERROR, true, prepend, format, args);
    }
}

void Logger::log(LogLevel logLevel, bool printPrepend, std::string prepend, const char* format, va_list args) {
    if(shouldOnlyPrintSpecifiedClasses && !shouldPrintForClass(className)) {
        return;
    }

    std::string logLevelStr = "";
    switch(logLevel) {
        case ERROR:
            logLevelStr = "ERROR";
            break;
        case DEBUG:
            logLevelStr = "DEBUG";
            break;
        case INFO:
            logLevelStr = "INFO";
            break;
    }

    auto timestamp = std::chrono::system_clock::now();
    std::time_t time = std::chrono::system_clock::to_time_t(timestamp);

    char buff[20];
    strftime(buff, 20, "%Y-%m-%d %H:%M:%S", std::localtime(&time));
    printf("[%s][%s][%s] ", buff, className.c_str(), logLevelStr.c_str());

    if(printPrepend) {
        printf("%s", prepend.c_str());
    }

    vprintf(format, args);
    printf("\n");
}

bool Logger::shouldPrintForClass(std::string className) {
    for(int i = 0; i < sizeof(classNamesToPrint); i++) {
        if(classNamesToPrint[i] == className) {
            return true;
        }
    }

    return false;
}