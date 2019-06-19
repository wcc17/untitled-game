#include "../../includes/scene/SceneManager.h"

void SceneManager::initialize(std::shared_ptr<EventBus> eventBus) {
    scene.initialize(AssetPath::SCENE_TILEMAP); //TODO: this should be decided else where when switching scene logic is implemented. Probably in a GameManager one scene up

    textureManager.loadTexture(AssetPath::PLAYER_TEXTURE);
    playerManager.initialize(eventBus, textureManager.getTexture(AssetPath::PLAYER_TEXTURE), scene.getPlayerCollidable());

    textureManager.loadTexture(AssetPath::NPC_TEXTURE);
    npcManager.initialize(scene.getNpcCollidables(), textureManager.getTexture(AssetPath::NPC_TEXTURE));

    collisionManager.initialize(eventBus);
}

void SceneManager::update(sf::Time elapsedTime) {
    playerManager.update(elapsedTime, scene.getMapTileSize());
    npcManager.update(elapsedTime);
    collisionManager.handleCollisions(playerManager.getPlayer(), npcManager.getNpcEntities(), scene.getMapCollidables());
}

void SceneManager::draw(sf::RenderWindow* window) {
    window->setView(playerManager.getView());
    window->draw(scene);
    npcManager.draw(window);
    playerManager.draw(window);
}

void SceneManager::release() {
    textureManager.releaseTextures();
    scene.release(); //TODO: will eventually be called somewhere else when the scene changes
    npcManager.release();
}