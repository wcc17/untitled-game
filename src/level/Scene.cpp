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
    mapSizeInTiles = sf::Vector2u(map.getTileCount().x, map.getTileCount().y);
    tileSize = sf::Vector2u(map.getTileSize().x, map.getTileSize().y);
    mapSizeInPixels = sf::Vector2u(mapSizeInTiles.x * tileSize.x, mapSizeInTiles.y * tileSize.y);


    const auto& layers = map.getLayers();
    for(const auto& layer : layers) {
        if(layer->getType() == tmx::Layer::Type::Tile) {
            loadTileLayer(layer->getLayerAs<tmx::TileLayer>(), tileset, map.getTileCount(), map.getTileSize());
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

sf::Vector2u Scene::getMapSizeInPixels() {
    return this->mapSizeInPixels;
}

sf::Vector2u Scene::getMapSizeInTiles() {
    return this->mapSizeInPixels;
}

sf::Vector2u Scene::getMapTileSize() {
    return this->mapSizeInPixels;
}

void Scene::release() {
    ObjectMap::release();
//    TileMap::release(); not actually needed right now
}