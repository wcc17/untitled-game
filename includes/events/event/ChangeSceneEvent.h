#ifndef NEWNEW_CHANGESCENEEVENT_H
#define NEWNEW_CHANGESCENEEVENT_H

#include "../Event.h"
#include "../../collisions/Collidable.h"

class ChangeSceneEvent : public Event {
public:
    ChangeSceneEvent(const Collidable& door): door(door) {}
    const Collidable& door;
};

#endif //NEWNEW_CHANGESCENEEVENT_H
