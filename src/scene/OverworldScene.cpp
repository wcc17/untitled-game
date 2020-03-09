#include "../../includes/scene/OverworldScene.h"

void OverworldScene::initialize(
        std::shared_ptr<EventBus> eventBus,
        std::string sceneName,
        std::string previousSceneName,
        TextureManager& textureManager,
        sf::Font* font,
        sf::Vector2u windowSize,
        sf::Vector2f defaultWindowSize) {

    Scene::initialize(eventBus, sceneName, previousSceneName, textureManager, font, windowSize, defaultWindowSize);

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
    uiManager.initialize(eventBus, textureManager, font, windowSize, defaultWindowSize, sceneName);
}

void OverworldScene::update(sf::Time elapsedTime, bool isPaused, sf::RenderTexture& renderTexture, sf::View& view) {
    if(!isPaused) {
        player->update(elapsedTime);
        npcManager.update(elapsedTime);
        collisionManager.checkAllCollisions(player, npcManager.getNpcEntities());
    }

    uiManager.update(renderTexture, view, elapsedTime);
}

void OverworldScene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = texture;

    for(sf::VertexArray vertexArray : vertices) {
        target.draw(vertexArray, states);
    }

    target.draw(*player);
    npcManager.drawToRenderTexture(static_cast<sf::RenderTexture&>(target));
    uiManager.drawToRenderTexture(static_cast<sf::RenderTexture&>(target));
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

void OverworldScene::openDialogue(std::string dialogueTextAssetName) {
    uiManager.openDialogue(dialogueTextAssetName);
}

void OverworldScene::closeDialogue() {
    uiManager.closeCurrentMenuOrDialogue();
}

void OverworldScene::handleControllerMenuButtonPressed() {
    uiManager.handleControllerMenuButtonPressed();
}

void OverworldScene::handleControllerActionButtonPressed() {
    uiManager.handleControllerActionButtonPressed();
}

void OverworldScene::handleControllerCancelButtonPressed() {
    uiManager.handleControllerCancelButtonPressed();
}

void OverworldScene::handleControllerMenuMoveButtonPressed(MoveDirection direction) {
    uiManager.handleControllerMenuMoveButtonPressed(direction);
}

void OverworldScene::release(TextureManager& textureManager) {
    uiManager.release(textureManager);
    player->release();
    sceneMap.release(textureManager);
    npcManager.release(textureManager);
}