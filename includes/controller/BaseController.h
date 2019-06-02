//
// Created by William Curry on 2019-06-01.
//

#ifndef NEWNEW_BASECONTROLLER_H
#define NEWNEW_BASECONTROLLER_H


#include <SFML/Window/Keyboard.hpp>

class BaseController {

public:
    virtual void handleInput() {};
    virtual void handleKeyPressedEvent(sf::Keyboard::Key key) {};
    virtual void handleKeyReleasedEvent(sf::Keyboard::Key key) {};
};

#endif //NEWNEW_BASECONTROLLER_H
