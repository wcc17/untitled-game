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
    sf::Texture texture;
    std::vector<sf::VertexArray> vertices;
    void loadTileMap();

private:
    std::string tileMapPath;
    void loadTileLayer(tmx::TileLayer layer, tmx::Tileset tileset, tmx::Vector2u mapSizeInTiles, tmx::Vector2u tileSize);
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
};


#endif //NEWNEW_TILEMAP_H
