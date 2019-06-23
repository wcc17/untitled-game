#ifndef NEWNEW_EXITGAMEEVENT_H
#define NEWNEW_EXITGAMEEVENT_H

#include "../Event.h"
#include <string>

class ExitGameEvent : public Event {
public:
    ExitGameEvent(std::string exitMessage) : exitMessage(exitMessage) {};
    const std::string exitMessage;
};

#endif //NEWNEW_EXITGAMEEVENT_H
