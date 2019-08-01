#ifndef NEWNEW_KEYBOARDCONTROLLER_H
#define NEWNEW_KEYBOARDCONTROLLER_H

#include <SFML/Window/Keyboard.hpp>
#include "BaseController.h"
#include "../entity/player/Player.h"
#include "../events/event/ControllerMoveEvent.h"
#include "../events/event/ControllerMenuEvent.h"
#include "../events/event/ControllerCancelEvent.h"
#include "../events/event/ControllerMenuMoveEvent.h"

class KeyboardController : public BaseController {

public:
    void initialize(std::shared_ptr<EventBus> eventBus);
    void handleInput(std::vector<sf::Event> sfEvents);
    void handleKeyPressedEvent(sf::Keyboard::Key key);
    void handleKeyReleasedEvent(sf::Keyboard::Key key);

private:
    static Logger logger;
};


#endif //NEWNEW_KEYBOARDCONTROLLER_H
