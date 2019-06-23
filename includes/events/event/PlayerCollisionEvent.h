#ifndef NEWNEW_PLAYERCOLLISIONEVENT_H
#define NEWNEW_PLAYERCOLLISIONEVENT_H

#include "../Event.h"
#include "../../collisions/Collidable.h"

class PlayerCollisionEvent : public Event {
public:
    PlayerCollisionEvent(const Collidable& collision): collidedWith(collision) {}
    const Collidable& collidedWith;
};

#endif //NEWNEW_PLAYERCOLLISIONEVENT_H
