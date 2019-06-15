#include "../../includes/level/ObjectMap.h"

const static std::string NOTYPE_OBJECT_TYPE = "notype";
const static std::string DOOR_OBJECT_TYPE = "door";
const static std::string SIGN_OBJECT_TYPE = "sign";
const static std::string WALL_OBJECT_TYPE = "wall";
const static std::string NPC_OBJECT_TYPE = "npc";

void ObjectMap::loadObjectLayer(tmx::ObjectGroup layer) {
    std::string layerName = layer.getName();
    for(int i = 0; i < layer.getObjects().size(); i++) {
        tmx::Object object = layer.getObjects()[i];

        if(object.getShape() == tmx::Object::Shape::Rectangle) {
            loadRectangleObjects(object, layerName);
        } else if(object.getShape() == tmx::Object::Shape::Polygon) {
            printf("NOTE: polygon collision is more complicated than AABB, haven't found a situation yet where I NEED polygons\n");
        } else {
            printf("this object shape is not yet supported\n");
        }
    }
}

void ObjectMap::loadRectangleObjects(tmx::Object object, std::string layerName) {
    tmx::FloatRect boundingBox = object.getAABB();
    std::string objectName = object.getName();

    sf::Vector2f position(boundingBox.left, boundingBox.top);
    sf::Vector2f size(boundingBox.width, boundingBox.height);

    CollidableType type = getCollidableType(object.getType());
    Collidable collidable = Collidable(objectName, type, position, size);
    if(type == CollidableType::NPC) {
        npcCollidables.push_back(collidable);
    } else {
        mapCollidables.push_back(collidable);
    }
}

CollidableType ObjectMap::getCollidableType(std::string typeName) {

    if(typeName == DOOR_OBJECT_TYPE) {
        return CollidableType::DOOR;
    } else if(typeName == SIGN_OBJECT_TYPE) {
        return CollidableType::SIGN;
    } else if(typeName == WALL_OBJECT_TYPE) {
        return CollidableType::WALL;
    } else if(typeName == NPC_OBJECT_TYPE) {
        return CollidableType::NPC;
    }

    printf("this type not yet supported\n");
    return CollidableType::NO_TYPE;
}

std::vector<Collidable> ObjectMap::getMapCollidables() {
    return this->mapCollidables;
}

std::vector<Collidable> ObjectMap::getNpcCollidables() {
    return this->npcCollidables;
}

void ObjectMap::release() {
    mapCollidables.clear();
    npcCollidables.clear();
}