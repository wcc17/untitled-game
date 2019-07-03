#ifndef NEWNEW_CLOSEDIALOGUEEVENT_H
#define NEWNEW_CLOSEDIALOGUEEVENT_H

#include "../Event.h"
#include "../../collisions/Collidable.h"

class CloseDialogueEvent : public Event {
public:
    CloseDialogueEvent(const Collidable& interactedWith) : interactedWith(interactedWith) {};
    const Collidable& interactedWith;
};

#endif //NEWNEW_CLOSEDIALOGUEEVENT_H
