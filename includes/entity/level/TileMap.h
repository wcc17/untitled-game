#ifndef NEWNEW_TILEMAP_H
#define NEWNEW_TILEMAP_H


#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>

class TileMap {

public:
    TileMap(std::string tileMapPath);

protected:
    std::string tileMapPath;
    sf::Texture texture;
    std::vector<sf::VertexArray> vertices;

    void loadTileMap();
    void handleTileLayer(tmx::TileLayer layer, tmx::Tileset tileset, tmx::Vector2u mapSizeInTiles, tmx::Vector2u tileSize);
    bool isTileIdTransparent(uint32_t layerTileId);
};


#endif //NEWNEW_TILEMAP_H
