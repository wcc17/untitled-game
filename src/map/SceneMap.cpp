#include "../../includes/map/SceneMap.h"

void SceneMap::loadObjectLayer(const tmx::ObjectGroup& layer) {
    sceneObjectMap.loadObjectLayer(layer);
}

std::vector<std::shared_ptr<Collidable>>& SceneMap::getMapCollidables() {
    return sceneObjectMap.getMapCollidables();
}

std::vector<Collidable> SceneMap::getNpcCollidables() {
    return sceneObjectMap.getNpcCollidables();
}

std::map<std::string, sf::IntRect> SceneMap::getNpcMoveBoundariesMap() {
    return sceneObjectMap.getNpcMoveBoundariesMap();
}

Collidable SceneMap::getPlayerCollidable(std::string spawnName) {
    return sceneObjectMap.getPlayerCollidable(spawnName);
}

std::map<std::string, std::string> SceneMap::getNpcNameToNpcAssetNameMap() {
    return sceneObjectMap.getNpcNameToNpcAssetNameMap();
}

std::string SceneMap::getPlayerSpawnPointName(std::string sceneName) {
    return sceneObjectMap.getPlayerSpawnPointName(sceneName);
}

void SceneMap::release(TextureManager& textureManager) {
    Map::release(textureManager);
    sceneObjectMap.release();
}