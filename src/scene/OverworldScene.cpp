#include "../../includes/scene/OverworldScene.h"

void OverworldScene::initialize(
        std::shared_ptr<EventBus> eventBus,
        std::string sceneName,
        std::string previousSceneName,
        TextureManager& textureManager) {

    this->sceneName = sceneName;
    this->sceneMap = mapLoader.loadSceneMap(textureManager, sceneName);
    this->texture = sceneMap.getTileMapTexture();
    this->vertices = sceneMap.getVertices();

    collisionManager.initialize(eventBus);

    player = std::make_shared<Player>();
    textureManager.loadTexture(AssetPath::PLAYER_TEXTURE);
    player->initialize(eventBus, textureManager.getTexture(AssetPath::PLAYER_TEXTURE));

    std::string playerSpawnName = getPlayerSpawnNameForPreviousToCurrentSceneTransition(previousSceneName);
    player->initializeForScene(getPlayerCollidable(playerSpawnName), getMapTileSize());

    npcManager.initialize(
            eventBus,
            getNpcCollidables(),
            getNpcMoveBoundariesMap(),
            getNpcNameToPropertiesMap(),
            getMapTileSize(),
            textureManager);

    collisionManager.initializeForScene(getMapCollidables());
}

void OverworldScene::update(sf::Time elapsedTime) {
    player->update(elapsedTime);
    npcManager.update(elapsedTime);
    collisionManager.checkAllCollisions(player, npcManager.getNpcEntities());
}

void OverworldScene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = texture;

    for(sf::VertexArray vertexArray : vertices) {
        target.draw(vertexArray, states);
    }

    target.draw(*player);
    npcManager.drawToRenderTexture(static_cast<sf::RenderTexture&>(target));
}

sf::Vector2u OverworldScene::getMapTileSize() {
    return sceneMap.getTileSize();
}

std::vector<std::shared_ptr<Collidable>>& OverworldScene::getMapCollidables() {
    return sceneMap.getMapCollidables();
}

std::vector<Collidable> OverworldScene::getNpcCollidables() {
    return sceneMap.getNpcCollidables();
}

std::map<std::string, sf::IntRect> OverworldScene::getNpcMoveBoundariesMap() {
    return sceneMap.getNpcMoveBoundariesMap();
}

Collidable OverworldScene::getPlayerCollidable(std::string spawnName) {
    return sceneMap.getPlayerCollidable(spawnName);
}

std::map<std::string, std::vector<tmx::Property>> OverworldScene::getNpcNameToPropertiesMap() {
    return sceneMap.getNpcNameToPropertiesMap();
}

std::string OverworldScene::getPlayerSpawnNameForPreviousToCurrentSceneTransition(std::string sceneName) {
    return sceneMap.getPlayerSpawnNameForPreviousToCurrentSceneTransition(sceneName);
}

void OverworldScene::release(TextureManager& textureManager) {
    player->release();
    sceneMap.release(textureManager);
    npcManager.release(textureManager);
}