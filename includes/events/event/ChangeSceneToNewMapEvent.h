#ifndef NEWNEW_CHANGESCENETONEWMAPEVENT_H
#define NEWNEW_CHANGESCENETONEWMAPEVENT_H

#include "../Event.h"
#include "../../collisions/Collidable.h"

class ChangeSceneToNewMapEvent : public Event {
public:
    ChangeSceneToNewMapEvent(const Collidable& door): door(door) {}
    const Collidable& door;
};


#endif //NEWNEW_CHANGESCENETONEWMAPEVENT_H
