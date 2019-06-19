#ifndef NEWNEW_TILEMAP_H
#define NEWNEW_TILEMAP_H


#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class TileMap {

protected:
    std::vector<sf::VertexArray> vertices;
    void loadTileLayer(const tmx::TileLayer& layer, const tmx::Tileset& tileset, const tmx::Vector2u& mapSizeInTiles,
                       const tmx::Vector2u& tileSize);
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
