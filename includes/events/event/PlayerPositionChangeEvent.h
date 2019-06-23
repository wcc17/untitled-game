#ifndef NEWNEW_PLAYERPOSITIONCHANGEEVENT_H
#define NEWNEW_PLAYERPOSITIONCHANGEEVENT_H

#include <SFML/Graphics/Rect.hpp>
#include "../../events/Event.h"

class PlayerPositionChangeEvent : public Event {
public:
    PlayerPositionChangeEvent(const sf::FloatRect& playerBounds): playerBounds(playerBounds) {}
    const sf::FloatRect& playerBounds;
};

#endif //NEWNEW_PLAYERPOSITIONCHANGEEVENT_H
