#include "../../includes/manager/GameManager.h"

void GameManager::initialize() {
    eventBus = std::make_shared<EventBus>();

    keyboardController.initialize(eventBus);
    levelManager.initialize(eventBus);
}

void GameManager::update(sf::Time deltaTime, std::vector<sf::Event> sfEvents) {
    keyboardController.handleInput(sfEvents);
    levelManager.update(deltaTime);
}

void GameManager::draw(sf::RenderWindow* window) {
    levelManager.draw(window);
}

void GameManager::release() {
    levelManager.release();
    eventBus.reset();
}