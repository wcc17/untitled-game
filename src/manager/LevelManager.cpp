#include "../../includes/manager/LevelManager.h"

void LevelManager::initialize(std::shared_ptr<EventBus> eventBus) {
    level.initialize(AssetPath::LEVEL_TILEMAP); //TODO: this should be decided else where when switching level logic is implemented. Probably in a GameManager one level up

    viewManager.initialize(eventBus);
    viewManager.initializeViewForLevel(level.getMapSizeInPixels());

    textureManager.loadTexture(AssetPath::PLAYER_TEXTURE);
    player.initialize(textureManager.getTexture(AssetPath::PLAYER_TEXTURE), level.getMapSizeInPixels().x,
            level.getMapSizeInPixels().y, eventBus);

    collisionManager.initialize(eventBus);
}

void LevelManager::update(sf::Time elapsedTime) {
    viewManager.update(elapsedTime);
    player.update(elapsedTime, viewManager.getViewPosition());
    collisionManager.handleCollisions(player.getGlobalBounds(), level.getMapCollidables());
}

void LevelManager::draw(sf::RenderWindow* window) {
    window->setView(viewManager.getView());
    window->draw(level);
    window->draw(player);
}

void LevelManager::release() {
    textureManager.releaseTextures();
}