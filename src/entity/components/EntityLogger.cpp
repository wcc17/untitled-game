#include "../../../includes/entity/components/EntityLogger.h"

void EntityLogger::initialize(std::string className, std::string entityName) {
    this->logger = std::make_shared<Logger>(className);
    this->entityName = entityName;
}

void EntityLogger::logDebug(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logger->logDebugWithPrepend(entityName + " - ", format, args);
    va_end(args);
}

void EntityLogger::logError(const char* format, ...) {
    va_list args;
    va_start(args, format);
    logger->logErrorWithPrepend(entityName + " - ", format, args);
    va_end(args);
}