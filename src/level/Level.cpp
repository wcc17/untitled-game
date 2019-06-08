#include <cmath>
#include "../../includes/level/Level.h"
#include "../../includes/asset/AssetPath.h"

const float LEVEL_MOVEMENT_SPEED = 270.f;
//TODO: should an AnimatedEntity and Level both derive from a BaseEntity? Basically Entity without the animation stuff. Will help with scaling too
//TODO: at the very least, need a higher level place to set the scale and pass to Entitys and levels

Level::Level(float windowWidth, float windowHeight) : movement(0.f, 0.f) {

    this->speed = LEVEL_MOVEMENT_SPEED;
    this->scale(sf::Vector2f(5.f, 5.f));

    view.setCenter(sf::Vector2f(windowWidth / 2, windowHeight / 2));
    view.setSize(sf::Vector2f(windowWidth, windowHeight));

    this->loadTileMap();
}

void Level::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &texture;

    for(sf::VertexArray vertexArray : vertices) {
        target.draw(vertexArray, states);
    }
}

sf::View Level::getView() const {
    return this->view;
}

void Level::update(sf::Time deltaTime) {
    this->move(movement * deltaTime.asSeconds());

    //NOTE: rounding the position gets rid of weird artifacting/flickering that was introduced after tile maps. any negative repercussions?
    this->setPosition(std::round(this->getPosition().x), std::round(this->getPosition().y));
}

void Level::moveUp() {
    resetMovement();
    movement.y += speed;
}

void Level::moveLeft() {
    resetMovement();
    movement.x += speed;
}

void Level::moveDown() {
    resetMovement();
    movement.y -= speed;
}

void Level::moveRight() {
    resetMovement();
    movement.x -= speed;
}

void Level::stop() {
    resetMovement();
}

void Level::resetMovement() {
    movement.x = 0;
    movement.y = 0;
}

void Level::loadTileMap() {
    tmx::Map map;

    if(!map.load(AssetPath::LEVEL_TILEMAP)) {
        //TODO: exit the application after printing the error that the file couldn't be loaded
    }

    //NOTE: this assumes that each level is only going to have a single tileset
    tmx::Tileset tileset = map.getTilesets()[0];
    texture.loadFromFile(tileset.getImagePath());

    //tile count and tile size
    tmx::Vector2u mapSizeInTiles = map.getTileCount();
    tmx::Vector2u tileSize = map.getTileSize();
    const auto& layers = map.getLayers();
    for(const auto& layer : layers) {
        if(layer->getType() == tmx::Layer::Type::Tile) {
            handleTileLayer(layer->getLayerAs<tmx::TileLayer>(), tileset, mapSizeInTiles, tileSize);
        } else {
            printf("not supporting this type of layer yet");
        }
    }
}

void Level::handleTileLayer(tmx::TileLayer layer, tmx::Tileset tileset, tmx::Vector2u mapSizeInTiles, tmx::Vector2u tileSize) {

    //TODO: tiles currently aren't being flipped if I flipped them inside of the Tiled app. tile has ID and flipFlags member variables
    sf::VertexArray layerVertices;
    layerVertices.setPrimitiveType(sf::Quads);
    layerVertices.resize(mapSizeInTiles.x * mapSizeInTiles.y * 4);

    for(int i = 0; i < layer.getTiles().size(); i++) {

        const tmx::TileLayer::Tile layerTile = layer.getTiles()[i];
        if(!isTileIdTransparent(layerTile.ID)) {
            const tmx::Tileset::Tile* tilesetTile = tileset.getTile(layerTile.ID);
            const tmx::Vector2u tilesetTileImagePosition = tilesetTile->imagePosition;
            const tmx::Vector2u tilesetTileImageSize = tilesetTile->imageSize;

            sf::Vertex* quad = &layerVertices[i*4];

            int x = (i % mapSizeInTiles.x) * tileSize.x;
            int y = (i / mapSizeInTiles.x) * tileSize.y;

            quad[0].position = sf::Vector2f(x, y);
            quad[1].position = sf::Vector2f(x + tilesetTileImageSize.x, y);
            quad[2].position = sf::Vector2f(x + tilesetTileImageSize.x, y + tilesetTileImageSize.y);
            quad[3].position = sf::Vector2f(x, y + tilesetTileImageSize.y);

            quad[0].texCoords = sf::Vector2f(tilesetTileImagePosition.x, tilesetTileImagePosition.y);
            quad[1].texCoords = sf::Vector2f(tilesetTileImagePosition.x + tilesetTileImageSize.x, tilesetTileImagePosition.y);
            quad[2].texCoords = sf::Vector2f(tilesetTileImagePosition.x + tilesetTileImageSize.x, tilesetTileImagePosition.y + tilesetTileImageSize.y);
            quad[3].texCoords = sf::Vector2f(tilesetTileImagePosition.x, tilesetTileImagePosition.y + tilesetTileImageSize.y);
        }
    }

    vertices.push_back(layerVertices);
}

bool Level::isTileIdTransparent(uint32_t layerTileId) {
    //could also use tmx::Tileset.hasTile(ID)
    //the layer tiles use ID = 0 to represent transparency in the layer
    //passing ID = 1 to tmx::Tileset.getTile returns the TILESET tile with ID = 0. tmx knows to convert these two
    return layerTileId == 0;
}