#include "../../includes/controller/KeyboardController.h"
#include <iostream>

void KeyboardController::handleInput(Player* player) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        std::cout << "W key pressed" << std::endl;
        player->moveUp();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        std::cout << "A key pressed" << std::endl;
        player->moveLeft();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        std::cout << "S key pressed" << std::endl;
        player->moveDown();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        std::cout << "D key pressed" << std::endl;
        player->moveRight();
    } else {
        player->stop();
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
