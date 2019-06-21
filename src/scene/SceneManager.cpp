#include "../../includes/scene/SceneManager.h"

void SceneManager::initialize(std::shared_ptr<EventBus> eventBus, sf::Font* font, sf::RenderWindow* window) {
    scene.initialize(AssetPath::SCENE_TILEMAP); //TODO: this should be decided else where when switching scene logic is implemented. Probably in a GameManager one scene up?

    textureManager.loadTexture(AssetPath::PLAYER_TEXTURE);
    playerManager.initialize(eventBus, textureManager.getTexture(AssetPath::PLAYER_TEXTURE), scene.getPlayerCollidable());

    textureManager.loadTexture(AssetPath::NPC_TEXTURE);
    npcManager.initialize(scene.getNpcCollidables(), textureManager.getTexture(AssetPath::NPC_TEXTURE));

    textureManager.loadTexture(AssetPath::DIALOGUE_BOX_TEXTURE);

    textManager.initialize(eventBus, textureManager.getTexture(AssetPath::DIALOGUE_BOX_TEXTURE), font, playerManager.getView(), window);

    collisionManager.initialize(eventBus);
}

void SceneManager::update(sf::Time elapsedTime) {
    playerManager.update(elapsedTime, scene.getMapTileSize());
    npcManager.update(elapsedTime);
    collisionManager.handleCollisions(playerManager.getPlayer(), npcManager.getNpcEntities(), scene.getMapCollidables());
}

void SceneManager::draw(sf::RenderWindow* window) {
    window->setView(*playerManager.getView());
    window->draw(scene);
    npcManager.draw(window);
    playerManager.draw(window);
    textManager.draw(window);
}

void SceneManager::drawForDefaultView(sf::RenderWindow* window) {
    window->setView(window->getDefaultView());
    textManager.drawForDefaultView(window);
}

void SceneManager::release() {
    textureManager.releaseTextures();
    scene.release(); //TODO: will eventually be called somewhere else when the scene changes
    npcManager.release();
}