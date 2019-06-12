#include "../../includes/level/TileMap.h"

const static std::string NOTYPE_LAYER = "notype";
const static std::string DOOR_LAYER = "doors";
const static std::string SIGN_LAYER = "signs";

void TileMap::initialize(std::string tileMapPath) {
    this->tileMapPath = tileMapPath;
    this->loadTileMap();
}

void TileMap::loadTileMap() {
    tmx::Map map;

    if(!map.load(tileMapPath)) {
        //TODO: exit the application after printing the error that the file couldn't be loaded
    }

    //NOTE: this assumes that each level is only going to have a single tileset
    tmx::Tileset tileset = map.getTilesets()[0];
    texture.loadFromFile(tileset.getImagePath());

    //tile count and tile size
    tmx::Vector2u mapSizeInTiles = map.getTileCount();
    tmx::Vector2u tileSize = map.getTileSize();
    mapSizeInPixels = sf::Vector2f(mapSizeInTiles.x * tileSize.x, mapSizeInTiles.y * tileSize.y);

    const auto& layers = map.getLayers();
    for(const auto& layer : layers) {
        if(layer->getType() == tmx::Layer::Type::Tile) {
            loadTileLayer(layer->getLayerAs<tmx::TileLayer>(), tileset, mapSizeInTiles, tileSize);
        } else if(layer->getType() == tmx::Layer::Type::Object) {
            loadObjectLayer(layer->getLayerAs<tmx::ObjectGroup>());
        } else {
            printf("not supporting this type of layer yet\n");
        }
    }

    printf("done loading tile map\n");
}

void TileMap::loadTileLayer(tmx::TileLayer layer, tmx::Tileset tileset, tmx::Vector2u mapSizeInTiles, tmx::Vector2u tileSize) {
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

void TileMap::loadObjectLayer(tmx::ObjectGroup layer) {
    std::string layerName = layer.getName();
    for(int i = 0; i < layer.getObjects().size(); i++) {
        tmx::Object object = layer.getObjects()[i];

        if(object.getShape() == tmx::Object::Shape::Rectangle) {
            loadRectangleObjects(object, layerName);
        } else if(object.getShape() == tmx::Object::Shape::Polygon) {
            printf("NOTE: polygon collision is more complicated than AABB, haven't found a situation yet where I NEED polygons\n");
        } else {
            printf("this object shape is not yet supported\n");
        }
    }
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

void TileMap::loadRectangleObjects(tmx::Object object, std::string layerName) {
    tmx::FloatRect boundingBox = object.getAABB();
    std::string objectName = object.getName();

    sf::Vector2f position(boundingBox.left, boundingBox.top);
    sf::Vector2f size(boundingBox.width, boundingBox.height);

    CollidableType type = getCollidableType(layerName);
    collidables.push_back(Collidable (position, size, objectName, type));
}

CollidableType TileMap::getCollidableType(std::string layerName) {

    //TODO: would it be better to use object.getType() instead of the layer? this has already caused confusion
    if(layerName == NOTYPE_LAYER) {
        return CollidableType::NO_TYPE;
    } else if(layerName == DOOR_LAYER) {
        return CollidableType::DOOR;
    } else if(layerName == SIGN_LAYER) {
        return CollidableType::SIGN;
    }

    printf("this type not yet supported\n");
    return CollidableType::NO_TYPE;
}

sf::Vector2f TileMap::getMapSizeInPixels() {
    return this->mapSizeInPixels;
}