#include "../../includes/level/Scene.h"

void Scene::initialize(std::string tileMapPath) {
    this->tileMapPath = tileMapPath;
    this->loadTileMap();
}

void Scene::loadTileMap() {
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

void Scene::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    states.transform *= getTransform();
    states.texture = &texture;

    for(sf::VertexArray vertexArray : vertices) {
        target.draw(vertexArray, states);
    }
}

sf::Vector2f Scene::getMapSizeInPixels() {
    return this->mapSizeInPixels;
}

void Scene::release() {
    ObjectMap::release();
//    TileMap::release(); not actually needed right now
}