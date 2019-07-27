#include "../../includes/scene/ObjectMap.h"

const static std::string NOTYPE_OBJECT_TYPE = "notype";
const static std::string DOOR_OBJECT_TYPE = "door";
const static std::string SIGN_OBJECT_TYPE = "sign";
const static std::string WALL_OBJECT_TYPE = "wall";
const static std::string NPC_OBJECT_TYPE = "npc";
const static std::string NPC_MOVE_BOUNDARY_OBJECT_TYPE = "npc_move_boundary";
const static std::string PLAYER_OBJECT_TYPE = "player";
const static std::string MENU_OBJECT_TYPE = "menu";
const static std::string MENU_OPTION_OBJECT_TYPE = "menu_option";

ObjectMap::ObjectMap() : logger("ObjectMap") { }

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
    } else if(typeName == MENU_OBJECT_TYPE) {
        return ObjectType::MENU;
    } else if(typeName == MENU_OPTION_OBJECT_TYPE) {
        return ObjectType::MENU_OPTION;
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

    logger.logError("Object property value not found, letting game crash");
    return nullptr;
}

void ObjectMap::loadObjectLayer(const tmx::ObjectGroup& layer) { }
void ObjectMap::loadRectangleObjects(const tmx::Object& object) { }
void ObjectMap::release() {}
