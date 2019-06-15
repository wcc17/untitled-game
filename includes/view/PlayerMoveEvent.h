#ifndef NEWNEW_PLAYERMOVEEVENT_H
#define NEWNEW_PLAYERMOVEEVENT_H

#include <SFML/System.hpp>
#include "../events/Event.h"

class PlayerMoveEvent : public Event {
public:
    PlayerMoveEvent(sf::Vector2f viewCenter) : viewCenter(viewCenter) {};
    sf::Vector2f viewCenter;
};

#endif //NEWNEW_PLAYERMOVEEVENT_H
