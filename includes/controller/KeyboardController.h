#ifndef NEWNEW_KEYBOARDCONTROLLER_H
#define NEWNEW_KEYBOARDCONTROLLER_H

#include <SFML/Window/Keyboard.hpp>
#include "BaseController.h"
#include "../entity/player/Player.h"
#include "../scene/SceneManager.h"
#include "../events/event/ControllerMoveEvent.h"

class KeyboardController : public BaseController {

public:
    void initialize(std::shared_ptr<EventBus> eventBus);
    void handleInput(std::vector<sf::Event> sfEvents);
    void handleKeyPressedEvent(sf::Keyboard::Key key);
    void handleKeyReleasedEvent(sf::Keyboard::Key key);
};


#endif //NEWNEW_KEYBOARDCONTROLLER_H
