#include "../../includes/scene/Scene.h"

Logger Scene::logger("Scene");

void Scene::initialize(std::string sceneName, TextureManager& textureManager) {
    this->sceneName = sceneName;
    this->sceneMap = mapLoader.loadSceneMap(textureManager, sceneName);
    this->texture = sceneMap.getTileMapTexture();
    this->vertices = sceneMap.getVertices();
}

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = texture;

    for(sf::VertexArray vertexArray : vertices) {
        target.draw(vertexArray, states);
    }
}

sf::Vector2u Scene::getMapTileSize() {
    return this->sceneMap.getTileSize();
}

std::string Scene::getSceneName() {
    return this->sceneName;
}

std::vector<std::shared_ptr<Collidable>>& Scene::getMapCollidables() {
    return sceneMap.getMapCollidables();
}

std::vector<Collidable> Scene::getNpcCollidables() {
    return sceneMap.getNpcCollidables();
}

std::map<std::string, sf::IntRect> Scene::getNpcMoveBoundariesMap() {
    return sceneMap.getNpcMoveBoundariesMap();
}

Collidable Scene::getPlayerCollidable(std::string spawnName) {
    return sceneMap.getPlayerCollidable(spawnName);
}

std::map<std::string, std::vector<tmx::Property>> Scene::getNpcNameToPropertiesMap() {
    return sceneMap.getNpcNameToPropertiesMap();
}

std::string Scene::getPlayerSpawnPointName(std::string sceneName) {
    return sceneMap.getPlayerSpawnPointName(sceneName);
}


void Scene::release(TextureManager& textureManager) {
    sceneMap.release(textureManager);
}