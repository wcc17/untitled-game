#include "../../includes/manager/GameManager.h"

void GameManager::initialize() {
    levelManager.initialize();
}

void GameManager::update(sf::Time deltaTime) {
    keyboardController.handleInput(&levelManager);
    levelManager.update(deltaTime);
}

void GameManager::draw(sf::RenderWindow* window) {
    levelManager.draw(window);
}

void GameManager::release() {
    levelManager.release();
}