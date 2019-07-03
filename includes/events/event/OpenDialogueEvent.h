#ifndef NEWNEW_OPENDIALOGUEEVENT_H
#define NEWNEW_OPENDIALOGUEEVENT_H

#include "../Event.h"
#include "../../collisions/Collidable.h"

class OpenDialogueEvent : public Event {
public:
    OpenDialogueEvent(const sf::FloatRect& playerRect, const Collidable& interactedWith, MoveDirection playerFacingDirection)
        : playerRect(playerRect), interactedWith(interactedWith), playerFacingDirection(playerFacingDirection) {};
    const sf::FloatRect& playerRect;
    const Collidable& interactedWith;
    const MoveDirection playerFacingDirection;
};

#endif //NEWNEW_OPENDIALOGUEEVENT_H
