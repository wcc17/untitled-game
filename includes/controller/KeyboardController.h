//
// Created by William Curry on 2019-06-01.
//

#ifndef NEWNEW_KEYBOARDCONTROLLER_H
#define NEWNEW_KEYBOARDCONTROLLER_H

#include <SFML/Window/Keyboard.hpp>
#include "BaseController.h"

class KeyboardController : public BaseController {

public:
    void handleInput();
    void handleKeyPressedEvent(sf::Keyboard::Key key);
    void handleKeyReleasedEvent(sf::Keyboard::Key key);
};


#endif //NEWNEW_KEYBOARDCONTROLLER_H
