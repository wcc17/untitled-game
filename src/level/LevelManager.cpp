#include "../../includes/level/LevelManager.h"

void LevelManager::initialize(std::shared_ptr<EventBus> eventBus) {
    scene.initialize(AssetPath::LEVEL_TILEMAP); //TODO: this should be decided else where when switching level logic is implemented. Probably in a GameManager one level up

    viewManager.initialize(eventBus);
    viewManager.initializeViewForLevel(scene.getMapSizeInPixels());

    textureManager.loadTexture(AssetPath::PLAYER_TEXTURE);
    player.initialize(textureManager.getTexture(AssetPath::PLAYER_TEXTURE), scene.getMapSizeInPixels().x,
                      scene.getMapSizeInPixels().y, eventBus);

    textureManager.loadTexture(AssetPath::NPC_TEXTURE);
    npcManager.initialize(scene.getNpcCollidables(), textureManager.getTexture(AssetPath::NPC_TEXTURE));

    collisionManager.initialize(eventBus);
}

void LevelManager::update(sf::Time elapsedTime) {
    viewManager.update(elapsedTime);
    player.update(elapsedTime);
    npcManager.update(elapsedTime);
    collisionManager.handleCollisions(player, npcManager.getNpcEntities(), scene.getMapCollidables());
}

void LevelManager::draw(sf::RenderWindow* window) {
    window->setView(viewManager.getView());
    window->draw(scene);
    npcManager.draw(window);
    window->draw(player);
}

//TODO: should all of the "release" methods be in deconstructors instead? Some classes its not appropriate, but this one it is
void LevelManager::release() {
    textureManager.releaseTextures();
    scene.release(); //TODO: will eventually be called somewhere else when the level changes
}