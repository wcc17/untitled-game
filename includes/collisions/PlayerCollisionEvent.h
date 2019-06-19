#ifndef NEWNEW_PLAYERCOLLISIONEVENT_H
#define NEWNEW_PLAYERCOLLISIONEVENT_H

#include "../events/Event.h"
#include "Collidable.h"
#include "../entity/player/Player.h"

class PlayerCollisionEvent : public Event {
public:
    PlayerCollisionEvent(const Collidable& collision): collidedWith(collision) {}
    const Collidable& collidedWith;
};

#endif //NEWNEW_PLAYERCOLLISIONEVENT_H
