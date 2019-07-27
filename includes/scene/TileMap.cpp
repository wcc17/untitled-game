#include "TileMap.h"

void TileMap::loadTileLayer(const tmx::TileLayer& layer, const tmx::Tileset& tileset, const tmx::Vector2u& mapSizeInTiles,
                            const tmx::Vector2u& tileSize) {
    vertices.clear();

    sf::VertexArray layerVertices;
    layerVertices.setPrimitiveType(sf::Quads);
    layerVertices.resize(mapSizeInTiles.x * mapSizeInTiles.y * 4);

    for(int i = 0; i < layer.getTiles().size(); i++) {
        const tmx::TileLayer::Tile layerTile = layer.getTiles()[i];

        if(!isTileIdTransparent(layerTile.ID)) {
            sf::Vertex* quad = &layerVertices[i*4];
            const tmx::Tileset::Tile* tilesetTile = tileset.getTile(layerTile.ID);
            int x = (i % mapSizeInTiles.x) * tileSize.x;
            int y = (i / mapSizeInTiles.x) * tileSize.y;

            setVertexPositionForTile(quad, x, y, tilesetTile->imageSize);
            setVertexTextureCoordsForTile(quad, x, y, tilesetTile->imageSize, tilesetTile->imagePosition);

            if(tileHasFlip(layerTile.flipFlags)) {
                handleFlips(quad, layerTile.flipFlags);
            }
        }
    }

    //TODO: do i want support for a "foreground layer" that should be draw ABOVE the player
    vertices.push_back(layerVertices);
}

std::vector<sf::VertexArray> TileMap::getVertices() {
    return this->vertices;
}

bool TileMap::isTileIdTransparent(uint32_t layerTileId) {
    //NOTE: could also use tmx::Tileset.hasTile(ID)
    //the layer tiles use ID = 0 to represent transparency in the layer
    //passing ID = 1 to tmx::Tileset.getTile returns the TILESET tile with ID = 0. tmx knows to convert these two
    return layerTileId == 0;
}

bool TileMap::tileHasFlip(uint8_t flipFlags) {
    if(!isHorizontalFlip(flipFlags) && !isVerticalFlip(flipFlags) && !isDiagonalFlip(flipFlags)) {
        return false;
    }

    return true;
}

void TileMap::handleFlips(sf::Vertex* quad, uint8_t flipFlags) {
    bool isHorizontal = isHorizontalFlip(flipFlags);
    bool isVertical = isVerticalFlip(flipFlags);
    bool isDiagonal = isDiagonalFlip(flipFlags);

    //0000 = no change (checked in this->tileHasFlip(..))
    //0100 = vertical = swap y axis
    //1000 = horizontal = swap x axis
    //1100 = horiz + vert = swap both axes = horiz+vert = rotate 180 degrees
    //0010 = diag = rotate 90 degrees right and swap x axis
    //0110 = diag+vert = rotate 270 degrees right
    //1010 = horiz+diag = rotate 90 degrees right
    //1110 = horiz+vert+diag = rotate 90 degrees right and swap y axis
    if(!isHorizontal && isVertical && !isDiagonal) {
        flipY(quad);
    } else if(isHorizontal && !isVertical && !isDiagonal) {
        flipX(quad);
    } else if(isHorizontal && isVertical && !isDiagonal) {
        flipY(quad);
        flipX(quad);
    } else if(!isHorizontal && !isVertical && isDiagonal) {
        flipD(quad);
    } else if(!isHorizontal && isVertical && isDiagonal) {
        flipX(quad);
        flipD(quad);
    } else if(isHorizontal && !isVertical && isDiagonal) {
        flipY(quad);
        flipD(quad);
    } else if(isHorizontal && isVertical && isDiagonal) {
        flipY(quad);
        flipX(quad);
        flipD(quad);
    }
}

void TileMap::setVertexPositionForTile(sf::Vertex* quad, int x, int y, tmx::Vector2u tilesetTileImageSize) {
    quad[0].position = sf::Vector2f(x, y);
    quad[1].position = sf::Vector2f(x + tilesetTileImageSize.x, y);
    quad[2].position = sf::Vector2f(x + tilesetTileImageSize.x, y + tilesetTileImageSize.y);
    quad[3].position = sf::Vector2f(x, y + tilesetTileImageSize.y);
}

void TileMap::setVertexTextureCoordsForTile(sf::Vertex* quad, int x, int y, tmx::Vector2u tilesetTileImageSize,
                                            tmx::Vector2u tilesetTileImagePosition) {

    quad[0].texCoords = sf::Vector2f(tilesetTileImagePosition.x, tilesetTileImagePosition.y);
    quad[1].texCoords = sf::Vector2f(tilesetTileImagePosition.x + tilesetTileImageSize.x, tilesetTileImagePosition.y);
    quad[2].texCoords = sf::Vector2f(tilesetTileImagePosition.x + tilesetTileImageSize.x, tilesetTileImagePosition.y + tilesetTileImageSize.y);
    quad[3].texCoords = sf::Vector2f(tilesetTileImagePosition.x, tilesetTileImagePosition.y + tilesetTileImageSize.y);
}

bool TileMap::isHorizontalFlip(uint8_t flipFlags) {
    return (flipFlags & tmx::TileLayer::FlipFlag::Horizontal);
}

bool TileMap::isVerticalFlip(uint8_t flipFlags) {
    return (flipFlags & tmx::TileLayer::FlipFlag::Vertical);
}

bool TileMap::isDiagonalFlip(uint8_t flipFlags) {
    return (flipFlags & tmx::TileLayer::FlipFlag::Diagonal);
}

void TileMap::flipY(sf::Vertex* quad) {
    sf::Vector2f *v0 = &quad[0].texCoords;
    sf::Vector2f *v1 = &quad[1].texCoords;
    sf::Vector2f *v2 = &quad[2].texCoords;
    sf::Vector2f *v3 = &quad[3].texCoords;

    sf::Vector2f tmp = *v0;
    v0->y = v2->y;
    v1->y = v2->y;
    v2->y = tmp.y;
    v3->y = v2->y;
}

void TileMap::flipX(sf::Vertex* quad) {
    sf::Vector2f *v0 = &quad[0].texCoords;
    sf::Vector2f *v1 = &quad[1].texCoords;
    sf::Vector2f *v2 = &quad[2].texCoords;
    sf::Vector2f *v3 = &quad[3].texCoords;

    sf::Vector2f tmp = *v0;
    v0->x = v1->x;
    v1->x = tmp.x;
    v2->x = v3->x;
    v3->x = v0->x ;
}

void TileMap::flipD(sf::Vertex* quad) {
    sf::Vector2f *v1 = &quad[1].texCoords;
    sf::Vector2f *v3 = &quad[3].texCoords;

    sf::Vector2f tmp = *v1;
    v1->x = v3->x;
    v1->y = v3->y;
    v3->x = tmp.x;
    v3->y = tmp.y;
}