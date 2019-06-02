//
// Created by William Curry on 2019-06-01.
//

#include "../includes/EventHandler.h"

void EventHandler::handleEvents(sf::RenderWindow* window, BaseController* controller) {
    sf::Event event;
    while (!shouldExitGame && window->pollEvent(event)) {
        handleClosedEvent(event);
        handleKeyPressedEvent(event, controller);
        handleKeyReleasedEvent(event, controller);
    }
}

void EventHandler::handleClosedEvent(sf::Event event) {
    if (event.type == sf::Event::Closed) {
        this->shouldExitGame = true;
    }
}

void EventHandler::handleKeyPressedEvent(sf::Event event, BaseController* controller) {
    if (event.type == sf::Event::KeyPressed) {
        controller->handleKeyPressedEvent(event.key.code);
    }
}

void EventHandler::handleKeyReleasedEvent(sf::Event event, BaseController* controller) {
    if (event.type == sf::Event::KeyReleased) {
        controller->handleKeyReleasedEvent(event.key.code);
    }
}

bool EventHandler::getShouldExitGame() {
    return this->shouldExitGame;
}