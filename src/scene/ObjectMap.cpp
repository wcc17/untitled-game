#include "../../includes/scene/ObjectMap.h"

const static std::string NOTYPE_OBJECT_TYPE = "notype";
const static std::string DOOR_OBJECT_TYPE = "door";
const static std::string SIGN_OBJECT_TYPE = "sign";
const static std::string WALL_OBJECT_TYPE = "wall";
const static std::string NPC_OBJECT_TYPE = "npc";
const static std::string NPC_MOVE_BOUNDARY_OBJECT_TYPE = "npc_move_boundary";
const static std::string PLAYER_OBJECT_TYPE = "player";

Logger ObjectMap::logger("ObjectMap");

void ObjectMap::loadObjectLayer(const tmx::ObjectGroup& layer) {
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

void ObjectMap::loadRectangleObjects(const tmx::Object& object) {
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
        playerCollidable = collidable;
    } else if(type == ObjectType::NPC_MOVE_BOUNDARY) {
        sf::IntRect rect = sf::IntRect(position.x, position.y, size.x, size.y);
        npcMoveBoundaries.insert(std::make_pair(objectName, rect));
    } else if(type != ObjectType::NO_TYPE){
        mapCollidables.push_back(std::make_shared<Collidable>(collidable));
    }
}

ObjectType ObjectMap::determineObjectType(std::string typeName) {

    if(typeName == DOOR_OBJECT_TYPE) {
        return ObjectType::DOOR;
    } else if(typeName == SIGN_OBJECT_TYPE) {
        return ObjectType::SIGN;
    } else if(typeName == WALL_OBJECT_TYPE) {
        return ObjectType::WALL;
    } else if(typeName == NPC_OBJECT_TYPE) {
        return ObjectType::NPC;
    } else if(typeName == PLAYER_OBJECT_TYPE) {
        return ObjectType::PLAYER;
    } else if(typeName == NPC_MOVE_BOUNDARY_OBJECT_TYPE) {
        return ObjectType::NPC_MOVE_BOUNDARY;
    }

    logger.logError("this type not yet supported");
    return ObjectType::NO_TYPE;
}

std::string ObjectMap::getObjectPropertyValue(std::string propertyName, const std::vector<tmx::Property> objectProperties) {
    for(const tmx::Property property : objectProperties) {
        if(property.getType() == tmx::Property::Type::String && property.getName() == propertyName) {
            return property.getStringValue();
        }
    }
}

std::vector<std::shared_ptr<Collidable>>& ObjectMap::getMapCollidables() {
    return this->mapCollidables;
}

std::vector<Collidable> ObjectMap::getNpcCollidables() {
    return this->npcCollidables;
}

std::map<std::string, sf::IntRect> ObjectMap::getNpcMoveBoundariesMap() {
    return this->npcMoveBoundaries;
}

Collidable ObjectMap::getPlayerCollidable() {
    return this->playerCollidable;
}

std::map<std::string, std::string> ObjectMap::getNpcNameToNpcAssetNameMap() {
    return this->npcNameToNpcAssetNameMap;
}

void ObjectMap::release() {
    mapCollidables.clear();
    npcCollidables.clear();
}