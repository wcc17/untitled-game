#include "../../includes/manager/GameManager.h"

void GameManager::initialize(sf::RenderWindow* window) {
    eventBus = std::make_shared<EventBus>();
    fontManager.loadFont(AssetPath::OPENSANS_REGULAR);
    framerateCounter.initialize(fontManager.getFont(AssetPath::OPENSANS_REGULAR));
    keyboardController.initialize(eventBus);
    sceneManager.initialize(eventBus, fontManager.getFont(AssetPath::OPENSANS_REGULAR), window);
}

void GameManager::update(std::vector<sf::Event> sfEvents) {
    sf::Time deltaTime = framerateCounter.update();
    keyboardController.handleInput(sfEvents);
    sceneManager.update(deltaTime);
}

void GameManager::draw(sf::RenderWindow* window) {
    sceneManager.draw(window);
    window->setView(window->getDefaultView());

    sceneManager.drawForDefaultView(window);
    window->draw(framerateCounter.getFpsText());
}

void GameManager::release() {
    fontManager.releaseFonts();
    sceneManager.release();
    eventBus.reset();
}