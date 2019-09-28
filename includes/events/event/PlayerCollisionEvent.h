#ifndef NEWNEW_PLAYERCOLLISIONEVENT_H
#define NEWNEW_PLAYERCOLLISIONEVENT_H

#include "../Event.h"
#include "../../collisions/Collidable.h"

class PlayerCollisionEvent : public Event {
public:
    PlayerCollisionEvent(const sf::Vector2f& newPlayerPosition) : newPlayerPosition(newPlayerPosition) {}
    const sf::Vector2f& newPlayerPosition;
};

#endif //NEWNEW_PLAYERCOLLISIONEVENT_H
