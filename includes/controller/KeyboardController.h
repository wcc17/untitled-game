#ifndef NEWNEW_KEYBOARDCONTROLLER_H
#define NEWNEW_KEYBOARDCONTROLLER_H

#include <SFML/Window/Keyboard.hpp>
#include "BaseController.h"
#include "../entity/Player.h"
#include "../level/Level.h"

class KeyboardController : public BaseController {

public:
    void handleInput(Player* player, Level* level);
    void handleKeyPressedEvent(sf::Keyboard::Key key);
    void handleKeyReleasedEvent(sf::Keyboard::Key key);
};


#endif //NEWNEW_KEYBOARDCONTROLLER_H
