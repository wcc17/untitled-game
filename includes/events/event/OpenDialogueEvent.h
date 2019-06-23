#ifndef NEWNEW_OPENDIALOGUEEVENT_H
#define NEWNEW_OPENDIALOGUEEVENT_H

#include "../Event.h"
#include "../../collisions/Collidable.h"

class OpenDialogueEvent : public Event {
public:
    OpenDialogueEvent(const sf::FloatRect& playerRect, const Collidable& interactedWith) : playerRect(playerRect), interactedWith(interactedWith) {};
    const sf::FloatRect& playerRect;
    const Collidable& interactedWith;
};

#endif //NEWNEW_OPENDIALOGUEEVENT_H
