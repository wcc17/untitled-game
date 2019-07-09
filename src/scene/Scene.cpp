#include "../../includes/scene/Scene.h"

Logger Scene::logger("Scene");

void Scene::initialize(std::string sceneName) {
    this->sceneName = sceneName;
    this->loadTileMap();
}

void Scene::loadTileMap() {
    tmx::Map map;

    std::string sceneMapPath = AssetPath::getSceneMapPath(sceneName);
    if(!map.load(sceneMapPath)) {
        //TODO: exit the application after printing the error that the file couldn't be loaded
    }

    //TODO: this assumes that each scene is only going to have a single tileset
    tmx::Tileset tileset = map.getTilesets()[0];
    texture.loadFromFile(tileset.getImagePath()); //TODO: this should be loaded in TextureManager so that it can be released later

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
            logger.logError("not supporting this type of layer yet");
        }
    }

    logger.logDebug("done loading tile map");
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
    return this->mapSizeInTiles;
}

sf::Vector2u Scene::getMapTileSize() {
    return this->tileSize;
}

void Scene::release() {
    ObjectMap::release();
//    TileMap::release(); not actually needed right now
}