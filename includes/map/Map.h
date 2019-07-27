#ifndef NEWNEW_MAP_H
#define NEWNEW_MAP_H


#include <tmxlite/Map.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include "../asset/TextureManager.h"

class Map {

public:
    virtual void loadObjectLayer(const tmx::ObjectGroup& layer) {};
    virtual void release(TextureManager& textureManager) {
        textureManager.releaseTexture(tilesetImagePath);
    };

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

private:
    std::string tilesetImagePath;
    sf::Texture* tileMapTexture;
    sf::Vector2u mapSizeInTiles;
    sf::Vector2u tileSize;
    sf::Vector2u mapSizeInPixels;
    std::vector<sf::VertexArray> vertices;

};


#endif //NEWNEW_MAP_H
