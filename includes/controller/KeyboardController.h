#ifndef NEWNEW_KEYBOARDCONTROLLER_H
#define NEWNEW_KEYBOARDCONTROLLER_H

#include <SFML/Window/Keyboard.hpp>
#include "BaseController.h"
#include "../entity/character/Player.h"
#include "../LevelManager.h"

class KeyboardController : public BaseController {

public:
    void handleInput(LevelManager* levelManager);
    void handleKeyPressedEvent(sf::Keyboard::Key key);
    void handleKeyReleasedEvent(sf::Keyboard::Key key);
};


#endif //NEWNEW_KEYBOARDCONTROLLER_H
