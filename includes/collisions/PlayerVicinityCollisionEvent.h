#ifndef NEWNEW_PLAYERVICINITYCOLLISIONEVENT_H
#define NEWNEW_PLAYERVICINITYCOLLISIONEVENT_H

#include "../events/Event.h"
#include "Collidable.h"

class PlayerVicinityCollisionEvent : public Event {
public:
    PlayerVicinityCollisionEvent(const Collidable& collision): collidedWith(collision) {}
    const Collidable& collidedWith;
};

#endif //NEWNEW_PLAYERVICINITYCOLLISIONEVENT_H
