//
// Created by William Curry on 2019-06-01.
//

#ifndef NEWNEW_EVENTHANDLER_H
#define NEWNEW_EVENTHANDLER_H


#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "controller/BaseController.h"

class EventHandler {

public:
    void handleEvents(sf::RenderWindow* window, BaseController* controller);
    bool getShouldExitGame() const;

private:
    void handleClosedEvent(sf::Event event);
    void handleKeyPressedEvent(sf::Event event, BaseController* controller);
    void handleKeyReleasedEvent(sf::Event event, BaseController* controller);
    bool shouldExitGame = false;
};


#endif //NEWNEW_EVENTHANDLER_H
