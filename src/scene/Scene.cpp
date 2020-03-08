#include "../../includes/scene/Scene.h"

Logger Scene::logger("Scene");

void Scene::initialize(
        std::shared_ptr<EventBus> eventBus,
        std::string sceneName,
        std::string previousSceneName,
        TextureManager& textureManager,
        sf::Font* font,
        sf::Vector2u windowSize,
        sf::Vector2f defaultWindowSize) {
    this->sceneName = sceneName;
    this->eventBus = eventBus;
}

std::string Scene::getSceneName() {
    return this->sceneName;
}

void Scene::release(TextureManager& textureManager) {
    uiManager.release(textureManager);
}