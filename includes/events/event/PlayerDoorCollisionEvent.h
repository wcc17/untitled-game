#ifndef NEWNEW_PLAYERDOORCOLLISIONEVENT_H
#define NEWNEW_PLAYERDOORCOLLISIONEVENT_H

#include "../Event.h"
#include "../../collisions/Collidable.h"

class PlayerDoorCollisionEvent : public Event {
public:
    PlayerDoorCollisionEvent(const Collidable& collision): collidedWith(collision) {}
    const Collidable& collidedWith;
};

#endif //NEWNEW_PLAYERDOORCOLLISIONEVENT_H
