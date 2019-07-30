#include "../../includes/map/SceneMap.h"

const static std::string DEFAULT_SPAWN_NAME = "default_spawn";

SceneMap::SceneMap() : logger("SceneMap") {}

//TODO: should this return an object with all of the collidables instead of having a bunch of getter methods for them? This would better match MenuMap
void SceneMap::loadObjectLayer(const tmx::ObjectGroup& layer) {
    std::string layerName = layer.getName();
    for(int i = 0; i < layer.getObjects().size(); i++) {
        tmx::Object object = layer.getObjects()[i];

        if(object.getShape() == tmx::Object::Shape::Rectangle) {
            loadRectangleObjects(object);
        } else if(object.getShape() == tmx::Object::Shape::Polygon) {
            logger.logError("NOTE: polygon collision is more complicated than AABB, haven't found a situation yet where I NEED polygons");
        } else {
            logger.logError("this object shape is not yet supported");
        }
    }
}

void SceneMap::loadRectangleObjects(const tmx::Object &object) {
    tmx::FloatRect boundingBox = object.getAABB();
    std::string objectName = object.getName();

    sf::Vector2f position(boundingBox.left, boundingBox.top);
    sf::Vector2f size(boundingBox.width, boundingBox.height);

    ObjectType type = determineObjectType(object.getType());
    Collidable collidable = Collidable(objectName, type, position, size);
    if(type == ObjectType::NPC) {
        npcNameToNpcAssetNameMap.insert(std::make_pair(collidable.getName(), getObjectPropertyValue("assetName", object.getProperties())));
        npcCollidables.push_back(collidable);
    } else if(type == ObjectType::PLAYER) {
        std::string spawnName = collidable.getName(); //using spawnName as object name makes tiled map easier to read
        collidable.setName("player"); //rest of the game doesn't need the collidable name as the spawn name, makes more sense as Player
        playerCollidables.insert(std::make_pair(spawnName, collidable));
    } else if(type == ObjectType::NPC_MOVE_BOUNDARY) {
        sf::IntRect rect = sf::IntRect(position.x, position.y, size.x, size.y);
        npcMoveBoundaries.insert(std::make_pair(objectName, rect));
    } else if(type != ObjectType::NO_TYPE){
        mapCollidables.push_back(std::make_shared<Collidable>(collidable));
    }
}

std::vector<std::shared_ptr<Collidable>>& SceneMap::getMapCollidables() {
    return this->mapCollidables;
}

std::vector<Collidable> SceneMap::getNpcCollidables() {
    return this->npcCollidables;
}

std::map<std::string, sf::IntRect> SceneMap::getNpcMoveBoundariesMap() {
    return this->npcMoveBoundaries;
}

Collidable SceneMap::getPlayerCollidable(std::string spawnName) {
    try {
        return this->playerCollidables.at(spawnName);
    } catch (const std::out_of_range& e) {
        logger.logError("No spawn found for the player");
        throw e; //at the very least, should have an "default_spawn" playerCollidable. If not, let the game crash
    }
}

std::map<std::string, std::string> SceneMap::getNpcNameToNpcAssetNameMap() {
    return this->npcNameToNpcAssetNameMap;
}

std::string SceneMap::getPlayerSpawnPointName(std::string sceneName) {
    std::string spawnPointName = DEFAULT_SPAWN_NAME;

    if(sceneName != "") {
        spawnPointName = "from_" + sceneName;

        auto it = playerCollidables.find(spawnPointName);
        if(it == playerCollidables.end()) {
            spawnPointName = DEFAULT_SPAWN_NAME; //should always at least be default_spawn in playerCollidables if the from_ name doesn't exist
        }
    }

    return spawnPointName;
}

void SceneMap::release(TextureManager& textureManager) {
    Map::release(textureManager);
    mapCollidables.clear();
    npcCollidables.clear();
}