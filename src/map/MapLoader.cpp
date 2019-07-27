#include "../../includes/map/MapLoader.h"

//void MapLoader::loadMenuMap(TextureManager& textureManager) {
//    tmx::Map map;
//
//    std::string sceneMapPath = AssetPath::getSceneMapPath(SCENE_NAME);
//    if(!map.load(sceneMapPath)) {
//        //TODO: exit the application after printing the error that the file couldn't be loaded
//    }
//
//    tmx::Tileset tileset = map.getTilesets()[0];
//
//    this->tilesetImagePath = tileset.getImagePath();
//    textureManager.loadTexture(tilesetImagePath);
//    this->tileMapTexture = textureManager.getTexture(tilesetImagePath);
//
//    const auto& layers = map.getLayers();
//    for(const auto& layer : layers) {
//        if(layer->getType() == tmx::Layer::Type::Object) {
//            menuObjectMap.loadObjectLayer(layer->getLayerAs<tmx::ObjectGroup>());
//        }
//    }
//
//    MenuComponent playerMenuComponent = menuObjectMap.getPlayerMenuComponent();
//    playerMenuLayer.addMenuComponent(playerMenuComponent.getName(), playerMenuComponent); //TODO: can this be added in the for loop instead?
//    playerMenuLayer.setTexture(*tileMapTexture);
//
//    for(const auto& layer : layers) {
//        if(layer->getType() == tmx::Layer::Type::Tile) {
//            sf::VertexArray layerVertexArray = tileMap.loadTileLayer(layer->getLayerAs<tmx::TileLayer>(), tileset, map.getTileCount(), map.getTileSize());
//            playerMenuLayer.addLayerVertices(layer->getName(), layerVertexArray);
//        }
//    }
//}
//
//void Scene::loadTileMap(TextureManager& textureManager) {
//    tmx::Map map;
//
//    std::string sceneMapPath = AssetPath::getSceneMapPath(sceneName);
//    if(!map.load(sceneMapPath)) {
//        //TODO: exit the application after printing the error that the file couldn't be loaded
//    }
//
//    //TODO: this assumes that each scene is only going to have a single tileset
//    tmx::Tileset tileset = map.getTilesets()[0];
//
//    this->tilesetImagePath = tileset.getImagePath();
//    textureManager.loadTexture(tilesetImagePath);
//    texture = *textureManager.getTexture(tilesetImagePath);
//
//    //tile count and tile size
//    mapSizeInTiles = sf::Vector2u(map.getTileCount().x, map.getTileCount().y);
//    tileSize = sf::Vector2u(map.getTileSize().x, map.getTileSize().y);
//    mapSizeInPixels = sf::Vector2u(mapSizeInTiles.x * tileSize.x, mapSizeInTiles.y * tileSize.y);
//
//    const auto& layers = map.getLayers();
//    for(const auto& layer : layers) {
//        if(layer->getType() == tmx::Layer::Type::Tile) {
//            sf::VertexArray layerVertexArray = tileMap.loadTileLayer(layer->getLayerAs<tmx::TileLayer>(), tileset, map.getTileCount(), map.getTileSize());
//            this->vertices.push_back(layerVertexArray);
//        } else if(layer->getType() == tmx::Layer::Type::Object) {
//            sceneObjectMap.loadObjectLayer(layer->getLayerAs<tmx::ObjectGroup>());
//        } else {
//            logger.logError("not supporting this type of layer yet");
//        }
//    }
//
//    logger.logDebug("done loading tile map");
//}
