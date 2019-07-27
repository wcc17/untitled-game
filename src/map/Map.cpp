#include "../../includes/map/Map.h"

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