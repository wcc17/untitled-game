#ifndef NEWNEW_KEYBOARDCONTROLLER_H
#define NEWNEW_KEYBOARDCONTROLLER_H

#include <SFML/Window/Keyboard.hpp>
#include "BaseController.h"
#include "../entity/player/Player.h"
#include "../level/LevelManager.h"

class KeyboardController : public BaseController {

public:
    void initialize(std::shared_ptr<EventBus> eventBus);
    void handleInput(std::vector<sf::Event> sfEvents);
    void handleKeyPressedEvent(sf::Keyboard::Key key);
    void handleKeyReleasedEvent(sf::Keyboard::Key key);

private:
    bool shouldSendStopMovementEvent = true;
};


#endif //NEWNEW_KEYBOARDCONTROLLER_H
