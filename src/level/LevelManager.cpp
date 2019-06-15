#include "../../includes/level/LevelManager.h"

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
    player.update(elapsedTime);
    collisionManager.handleCollisions(getEntityCollidables(), level.getMapCollidables());
}

void LevelManager::draw(sf::RenderWindow* window) {
    window->setView(viewManager.getView());
    window->draw(level);
    window->draw(player);
}

std::vector<Collidable> LevelManager::getEntityCollidables() {
    //NOTE: recreating this vector every frame. Pointers might be better, but then I'll have to worry about
    //removing (dead, removed?) entities from it when NPCs are introduced
    std::vector<Collidable> entityCollidables;
    entityCollidables.push_back(player);

    return entityCollidables;
}

//TODO: should all of the "release" methods be in deconstructors instead? Some classes its not appropriate, but this one it is
void LevelManager::release() {
    textureManager.releaseTextures();
    level.release(); //TODO: will eventually be called somewhere else when the level changes
}