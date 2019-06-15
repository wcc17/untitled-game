#ifndef NEWNEW_PLAYERCOLLISIONEVENT_H
#define NEWNEW_PLAYERCOLLISIONEVENT_H

#include "../events/Event.h"
#include "Collidable.h"

class PlayerCollisionEvent : public Event {
public:
    PlayerCollisionEvent(std::pair<Collidable, Collidable> collision): collision(collision) {}
    std::pair<Collidable, Collidable> getCollision() {
        return this->collision;
    }
private:
    std::pair<Collidable, Collidable> collision;
};

#endif //NEWNEW_PLAYERCOLLISIONEVENT_H
