#include "../../includes/controller/KeyboardController.h"
#include <iostream>

void KeyboardController::handleInput() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        std::cout << "W key pressed" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        std::cout << "A key pressed" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        std::cout << "S key pressed" << std::endl;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        std::cout << "D key pressed" << std::endl;
    }
}

void KeyboardController::handleKeyPressedEvent(sf::Keyboard::Key key) {
    switch(key) {
        case sf::Keyboard::Enter:
            std::cout << "Enter key pressed" << std::endl;
            break;
        default:
            break;
    }
}

void KeyboardController::handleKeyReleasedEvent(sf::Keyboard::Key key) {
    switch(key) {
        case sf::Keyboard::Enter:
            std::cout << "Enter key released" << std::endl;
            break;
        default:
            break;
    }
}
