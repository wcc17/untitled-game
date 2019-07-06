#ifndef NEWNEW_ENTITYLOGGER_H
#define NEWNEW_ENTITYLOGGER_H

#include <string>
#include "../../util/Logger.h"

class EntityLogger {
public:
    void initialize(std::string className, std::string entityName);
    void logDebug(const char* format, ...);
    void logError(const char* format, ...);
private:
    std::shared_ptr<Logger> logger;
    std::string entityName;
};


#endif //NEWNEW_ENTITYLOGGER_H
