#include "../../includes/map/MapLoader.h"

Logger MapLoader::logger("MapLoader");

//TODO: these (loadMenuMap and loadSceneMap) should be split up into private methods
MenuLayer MapLoader::loadMenuLayerMap(TextureManager& textureManager, std::string menuName) {
    MenuMap menuMap;
    MenuLayer menuLayer;
    tmx::Map map;

    std::string menuMapPath = AssetPath::getMenuLayerMapPath(menuName);
    if(!map.load(menuMapPath)) {
        //TODO: exit the application after printing the error that the file couldn't be loaded
    }

    tmx::Tileset tileset = map.getTilesets()[0];

    menuLayer.setTilesetImagePath(tileset.getImagePath());
    textureManager.loadTexture(tileset.getImagePath());
    menuLayer.setTexture(*textureManager.getTexture(tileset.getImagePath()));

    const auto& layers = map.getLayers();
    for(const auto& layer : layers) {
        if(layer->getType() == tmx::Layer::Type::Object) {
            const tmx::ObjectGroup& objectLayer = layer->getLayerAs<tmx::ObjectGroup>();
            menuLayer.addMenuComponent(objectLayer.getName(), menuMap.loadMenu(objectLayer.getName(), objectLayer.getObjects()));
        }
    }

    for(const auto& layer : layers) {
        if(layer->getType() == tmx::Layer::Type::Tile) {
            sf::VertexArray layerVertexArray = TileMap::loadTileLayer(layer->getLayerAs<tmx::TileLayer>(), tileset, map.getTileCount(), map.getTileSize());
            menuLayer.addLayerVertices(layer->getName(), layerVertexArray);
        }
    }

    return menuLayer;
}

SceneMap MapLoader::loadSceneMap(TextureManager& textureManager, std::string sceneName) {
    SceneMap sceneObjectMap;
    tmx::Map map;

    std::string sceneMapPath = AssetPath::getSceneMapPath(sceneName);
    if(!map.load(sceneMapPath)) {
        //TODO: exit the application after printing the error that the file couldn't be loaded
    }

    //TODO: this assumes that each scene is only going to have a single tileset
    tmx::Tileset tileset = map.getTilesets()[0];

    sceneObjectMap.setTilesetImagePath(tileset.getImagePath());
    textureManager.loadTexture(sceneObjectMap.getTilesetImagePath());
    sceneObjectMap.setTileMapTexture(textureManager.getTexture(sceneObjectMap.getTilesetImagePath()));

    //tile count and tile size
    sceneObjectMap.setMapSizeInTiles(sf::Vector2u(map.getTileCount().x, map.getTileCount().y));
    sceneObjectMap.setTileSize(sf::Vector2u(map.getTileSize().x, map.getTileSize().y));
    sceneObjectMap.setMapSizeInPixels(sf::Vector2u(sceneObjectMap.getMapSizeInTiles().x * sceneObjectMap.getTileSize().x,
                                                   sceneObjectMap.getMapSizeInTiles().y * sceneObjectMap.getTileSize().y));

    const auto& layers = map.getLayers();
    for(const auto& layer : layers) {
        if(layer->getType() == tmx::Layer::Type::Tile) {
            sf::VertexArray layerVertexArray = TileMap::loadTileLayer(layer->getLayerAs<tmx::TileLayer>(), tileset, map.getTileCount(), map.getTileSize());
            sceneObjectMap.addVertices(layerVertexArray);
        } else if(layer->getType() == tmx::Layer::Type::Object) {
            sceneObjectMap.loadObjectLayer(layer->getLayerAs<tmx::ObjectGroup>());
        } else {
            logger.logError("not supporting this type of layer yet");
        }
    }

    logger.logDebug("done loading tile map");
    return sceneObjectMap;
}
