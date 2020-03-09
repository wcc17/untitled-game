#ifndef NEWNEW_CHANGESCENETONEWMAPEVENT_H
#define NEWNEW_CHANGESCENETONEWMAPEVENT_H

#include "../Event.h"

class ChangeSceneToNewMapEvent : public Event {
public:
    ChangeSceneToNewMapEvent(const std::string newSceneName): newSceneName(newSceneName) {}
    const std::string newSceneName;
};


#endif //NEWNEW_CHANGESCENETONEWMAPEVENT_H
