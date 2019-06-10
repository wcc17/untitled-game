#ifndef NEWNEW_TILEMAP_H
#define NEWNEW_TILEMAP_H


#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <tmxlite/Map.hpp>
#include <tmxlite/ObjectGroup.hpp>
#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include "../collidable/CollidableType.h"
#include "../collidable/Collidable.h"

class TileMap {

public:
    void initialize(std::string tileMapPath);
    sf::Vector2f getMapSizeInPixels();

protected:
    sf::Texture texture;
    std::vector<sf::VertexArray> vertices;
    std::vector<Collidable> collidables;
    sf::Vector2f mapSizeInPixels;
    void loadTileMap();

private:
    std::string tileMapPath;
    void loadTileLayer(tmx::TileLayer layer, tmx::Tileset tileset, tmx::Vector2u mapSizeInTiles, tmx::Vector2u tileSize);
    void loadObjectLayer(tmx::ObjectGroup layer);
    bool isTileIdTransparent(uint32_t layerTileId);
    void setVertexPositionForTile(sf::Vertex* quad, int x, int y, tmx::Vector2u tilesetTileImageSize);
    void setVertexTextureCoordsForTile(sf::Vertex* quad, int x, int y, tmx::Vector2u tilesetTileImagePosition,
            tmx::Vector2u tilesetTileImageSize);
    bool tileHasFlip(uint8_t flipFlags);
    bool isHorizontalFlip(uint8_t flipFlags);
    bool isVerticalFlip(uint8_t flipFlags);
    bool isDiagonalFlip(uint8_t flipFlags);
    void handleFlips(sf::Vertex* quad, uint8_t flipFlags); //NOTE: taken from https://github.com/fallahn/tmxlite/blob/master/SFMLExample/src/SFMLOrthogonalLayer.hpp in doFlips function
    void flipY(sf::Vertex* quad);
    void flipX(sf::Vertex* quad);
    void flipD(sf::Vertex* quad);
    void loadRectangleObjects(tmx::Object object, std::string layerName);
    CollidableType getCollidableType(std::string layerName);
};


#endif //NEWNEW_TILEMAP_H
