#include "../../includes/scene/OverworldScene.h"

void OverworldScene::initialize(std::string sceneName, TextureManager& textureManager) {
    this->sceneName = sceneName;
    this->sceneMap = mapLoader.loadSceneMap(textureManager, sceneName);
    this->texture = sceneMap.getTileMapTexture();
    this->vertices = sceneMap.getVertices();
}

void OverworldScene::update() {

}

void OverworldScene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = texture;

    for(sf::VertexArray vertexArray : vertices) {
        target.draw(vertexArray, states);
    }
}

sf::Vector2u OverworldScene::getMapTileSize() {
    return this->sceneMap.getTileSize();
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
    sceneMap.release(textureManager);
}