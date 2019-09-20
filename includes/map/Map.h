#ifndef NEWNEW_MAP_H
#define NEWNEW_MAP_H


#include <tmxlite/Map.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "../asset/TextureManager.h"
#include "ObjectType.h"
#include "../util/Logger.h"

class Map {

public:
    Map();
    ObjectType determineObjectType(std::string typeName);

    void addVertices(sf::VertexArray vertexArray);
    std::vector<sf::VertexArray> getVertices();
    std::string getTilesetImagePath();
    sf::Texture* getTileMapTexture();
    sf::Vector2u getMapSizeInTiles();
    sf::Vector2u getTileSize();
    sf::Vector2u getMapSizeInPixels();
    void setTilesetImagePath(std::string tilesetImagePath);
    void setTileMapTexture(sf::Texture* texture);
    void setMapSizeInTiles(sf::Vector2u mapSizeInTiles);
    void setTileSize(sf::Vector2u tileSize);
    void setMapSizeInPixels(sf::Vector2u mapSizeInPixels);

    virtual void loadRectangleObjects(const tmx::Object& object);
    virtual void release(TextureManager& textureManager);
    static std::string getObjectPropertyStringValue(std::string propertyName, const std::vector<tmx::Property> objectProperties);
    static bool getObjectPropertyBoolValue(std::string propertyName, const std::vector<tmx::Property> objectProperties);

    static const std::string PROPERTY_NAME_ASSET_NAME;
    static const std::string PROPERTY_NAME_IS_AGGRESSIVE;
    static const std::string PROPERTY_NAME_NPC_TYPE;

private:
    std::string tilesetImagePath;
    sf::Texture* tileMapTexture;
    sf::Vector2u mapSizeInTiles;
    sf::Vector2u tileSize;
    sf::Vector2u mapSizeInPixels;
    std::vector<sf::VertexArray> vertices;
    Logger logger;

};


#endif //NEWNEW_MAP_H
