#include "../../includes/controller/KeyboardController.h"

void KeyboardController::handleInput(LevelManager* levelManager) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
        levelManager->handleMoveUp();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
        levelManager->handleMoveLeft();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
        levelManager->handleMoveDown();
    } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
        levelManager->handleMoveRight();
    } else {
        levelManager->handleMoveStop();
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