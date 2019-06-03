#include "../../includes/controller/KeyboardController.h"

void KeyboardController::handleInput(Player* player, Level* level) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        player->moveUp();
        level->moveUp();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        player->moveLeft();
        level->moveLeft();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        player->moveDown();
        level->moveDown();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        player->moveRight();
        level->moveRight();
    } else {
        player->stop();
        level->stop();
    }
}

void KeyboardController::handleKeyPressedEvent(sf::Keyboard::Key key) {
    switch(key) {
        case sf::Keyboard::Enter:
            break;
        default:
            break;
    }
}

void KeyboardController::handleKeyReleasedEvent(sf::Keyboard::Key key) {
    switch(key) {
        case sf::Keyboard::Enter:
            break;
        default:
            break;
    }
}
