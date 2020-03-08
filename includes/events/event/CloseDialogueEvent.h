#ifndef NEWNEW_CLOSEDIALOGUEEVENT_H
#define NEWNEW_CLOSEDIALOGUEEVENT_H

#include "../Event.h"
#include "../../collisions/Collidable.h"

class CloseDialogueEvent : public Event {
public:
    CloseDialogueEvent(std::string nameOfDialogueClosed) : nameOfDialogueClosed(nameOfDialogueClosed) {};
    const std::string nameOfDialogueClosed;
};

#endif //NEWNEW_CLOSEDIALOGUEEVENT_H
