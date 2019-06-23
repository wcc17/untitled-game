#ifndef NEWNEW_PLAYERVICINITYCOLLISIONEVENT_H
#define NEWNEW_PLAYERVICINITYCOLLISIONEVENT_H

#include "../Event.h"
#include "../../collisions/Collidable.h"

class PlayerVicinityCollisionEvent : public Event {
public:
    PlayerVicinityCollisionEvent(std::shared_ptr<Collidable> collision): collidedWith(collision) {}
    const std::shared_ptr<Collidable> collidedWith;
};

#endif //NEWNEW_PLAYERVICINITYCOLLISIONEVENT_H
