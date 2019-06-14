#ifndef NEWNEW_BASECONTROLLER_H
#define NEWNEW_BASECONTROLLER_H


#include <SFML/Window/Keyboard.hpp>
#include <SFML/Window/Event.hpp>
#include <vector>
#include "../events/EventBus.h"

class BaseController {

public:
    virtual void initialize(std::shared_ptr<EventBus> eventBus);
    virtual void handleInput() {};
    virtual void handleKeyPressedEvent(sf::Keyboard::Key key) {};
    virtual void handleKeyReleasedEvent(sf::Keyboard::Key key) {};
    virtual void handleSfEvents(std::vector<sf::Event> sfEvents);

protected:
    std::shared_ptr<EventBus> eventBus;
};

#endif //NEWNEW_BASECONTROLLER_H
