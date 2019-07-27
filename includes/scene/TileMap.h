#ifndef NEWNEW_TILEMAP_H
#define NEWNEW_TILEMAP_H


#include <tmxlite/TileLayer.hpp>
#include <tmxlite/Tileset.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include <SFML/Graphics/VertexArray.hpp>

class TileMap {
public:
    void loadTileLayer(const tmx::TileLayer& layer, const tmx::Tileset& tileset, const tmx::Vector2u& mapSizeInTiles,
                       const tmx::Vector2u& tileSize);
    std::vector<sf::VertexArray> getVertices();

protected:
    std::vector<sf::VertexArray> vertices;
    static bool isTileIdTransparent(uint32_t layerTileId);
    static void setVertexPositionForTile(sf::Vertex* quad, int x, int y, tmx::Vector2u tilesetTileImageSize);
    static void setVertexTextureCoordsForTile(sf::Vertex* quad, int x, int y, tmx::Vector2u tilesetTileImagePosition,
                                       tmx::Vector2u tilesetTileImageSize);
    static bool tileHasFlip(uint8_t flipFlags);
    static bool isHorizontalFlip(uint8_t flipFlags);
    static bool isVerticalFlip(uint8_t flipFlags);
    static bool isDiagonalFlip(uint8_t flipFlags);
    static void handleFlips(sf::Vertex* quad, uint8_t flipFlags); //NOTE: taken from https://github.com/fallahn/tmxlite/blob/master/SFMLExample/src/SFMLOrthogonalLayer.hpp in doFlips function
    static void flipY(sf::Vertex* quad);
    static void flipX(sf::Vertex* quad);
    static void flipD(sf::Vertex* quad);
};


#endif //NEWNEW_TILEMAP_H
