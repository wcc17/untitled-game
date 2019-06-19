#include "../../includes/manager/GameManager.h"

void GameManager::initialize() {
    eventBus = std::make_shared<EventBus>();

    keyboardController.initialize(eventBus);
    sceneManager.initialize(eventBus);
}

void GameManager::update(sf::Time deltaTime, std::vector<sf::Event> sfEvents) {
    keyboardController.handleInput(sfEvents);
    sceneManager.update(deltaTime);
}

void GameManager::draw(sf::RenderWindow* window) {
    sceneManager.draw(window);
}

void GameManager::release() {
    sceneManager.release();
    eventBus.reset();
}