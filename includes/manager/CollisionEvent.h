#ifndef NEWNEW_COLLISIONEVENT_H
#define NEWNEW_COLLISIONEVENT_H

#include <SFML/Graphics/Rect.hpp>
#include "../events/Event.h"
#include "../level/collidable/CollidableType.h"

//TODO: should everything that could "collide" dervie from a certain base class? Sprite? a new collidable?
//TODO: move this class, the collision manager, and the collidable folder to its own folder (collisions)
//TODO: at the same time, move LevelManager to the level folder.
//TODO: what if its an NPC on object collision? How do we identify who the event should go to?
class CollisionEvent : public Event {
public:
    CollisionEvent(CollidableType collidableType, sf::FloatRect a, sf::FloatRect b)
        : collidableType(collidableType), a(a), b(b) {}

private:
    CollidableType collidableType;
    sf::FloatRect a;
    sf::FloatRect b;
};

#endif //NEWNEW_COLLISIONEVENT_H
