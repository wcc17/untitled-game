#ifndef NEWNEW_ENTITYCOLLISIONEVENT_H
#define NEWNEW_ENTITYCOLLISIONEVENT_H

#include "../events/Event.h"
#include "Collidable.h"

class EntityCollisionEvent : public Event {
public:
    EntityCollisionEvent(std::pair<Collidable, Collidable> collision): collision(collision) {}
    std::pair<Collidable, Collidable> getCollision() {
        return this->collision;
    }
private:
    std::pair<Collidable, Collidable> collision;
};

#endif //NEWNEW_PLAYERCOLLISIONEVENT_H
