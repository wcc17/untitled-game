#include "../../includes/map/Map.h"

const static std::string NOTYPE_OBJECT_TYPE = "notype";
const static std::string DOOR_OBJECT_TYPE = "door";
const static std::string SIGN_OBJECT_TYPE = "sign";
const static std::string WALL_OBJECT_TYPE = "wall";
const static std::string NPC_OBJECT_TYPE = "npc";
const static std::string NPC_MOVE_BOUNDARY_OBJECT_TYPE = "npc_move_boundary";
const static std::string PLAYER_OBJECT_TYPE = "player";

const std::string Map::PROPERTY_NAME_ASSET_NAME = "assetName";
const std::string Map::PROPERTY_NAME_IS_AGGRESSIVE = "isAggressive";
const std::string Map::PROPERTY_NAME_NPC_TYPE = "npcType";

Map::Map() : logger("Map") { }

ObjectType Map::determineObjectType(std::string typeName) {

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

void Map::addVertices(sf::VertexArray vertexArray) {
    this->vertices.push_back(vertexArray);
}

std::vector<sf::VertexArray> Map::getVertices() {
    return vertices;
}

std::string Map::getTilesetImagePath() {
    return tilesetImagePath;
}

sf::Texture* Map::getTileMapTexture() {
    return tileMapTexture;
}

sf::Vector2u Map::getMapSizeInTiles() {
    return mapSizeInTiles;
}

sf::Vector2u Map::getTileSize() {
    return tileSize;
}

sf::Vector2u Map::getMapSizeInPixels() {
    return mapSizeInTiles;
}

void Map::setTilesetImagePath(std::string tilesetImagePath) {
    this->tilesetImagePath = tilesetImagePath;
}

void Map::setTileMapTexture(sf::Texture* texture) {
    this->tileMapTexture = texture;
}

void Map::setMapSizeInTiles(sf::Vector2u mapSizeInTiles) {
    this->mapSizeInTiles = mapSizeInTiles;
}

void Map::setTileSize(sf::Vector2u tileSize) {
    this->tileSize = tileSize;
}

void Map::setMapSizeInPixels(sf::Vector2u mapSizeInPixels) {
    this->mapSizeInPixels = mapSizeInPixels;
}

void Map::release(TextureManager& textureManager) {
    textureManager.releaseTexture(tilesetImagePath);
}

void Map::loadRectangleObjects(const tmx::Object& object) {}

std::string Map::getObjectPropertyStringValue(std::string propertyName, const std::vector<tmx::Property> objectProperties) {
    for(const tmx::Property property : objectProperties) {
        if(property.getType() == tmx::Property::Type::String && property.getName() == propertyName) {
            return property.getStringValue();
        }
    }

    return "";
}

bool Map::getObjectPropertyBoolValue(std::string propertyName, const std::vector<tmx::Property> objectProperties) {
    for(const tmx::Property property : objectProperties) {
        if(property.getType() == tmx::Property::Type::Boolean && property.getName() == propertyName) {
            return property.getBoolValue();
        }
    }

    return false;
}