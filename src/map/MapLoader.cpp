#include "../../includes/map/MapLoader.h"
#include "../../includes/map/MenuMap.h"

Logger MapLoader::logger("MapLoader");

MenuMap MapLoader::loadMenuMap(TextureManager& textureManager, std::string sceneName) {
    MenuMap menuMap;
    tmx::Map map;

    std::string sceneMapPath = AssetPath::getSceneMapPath(sceneName);
    if(!map.load(sceneMapPath)) {
        //TODO: exit the application after printing the error that the file couldn't be loaded
    }

    tmx::Tileset tileset = map.getTilesets()[0];

    menuMap.setTilesetImagePath(tileset.getImagePath());
    textureManager.loadTexture(menuMap.getTilesetImagePath());
//    menuMap.setTileMapTexture(textureManager.getTexture(menuMap.getTilesetImagePath()));

    const auto& layers = map.getLayers();
    for(const auto& layer : layers) {
        if(layer->getType() == tmx::Layer::Type::Object) {
            menuMap.loadObjectLayer(layer->getLayerAs<tmx::ObjectGroup>());
        }
    }

    //TODO: can this be added in the for loop instead without having playerMenuComponent in MenuObjectMap?
    MenuLayer playerMenuLayer;
    MenuComponent playerMenuComponent = menuMap.getMenuObjectMap().getPlayerMenuComponent();
    playerMenuLayer.addMenuComponent(playerMenuComponent.getName(), playerMenuComponent);
    playerMenuLayer.setTexture(*textureManager.getTexture(menuMap.getTilesetImagePath())); //TODO: shouldn't be setting this texture directly in playerMenuLayer. all the menus should be looking at the same tilemap texture

    for(const auto& layer : layers) {
        if(layer->getType() == tmx::Layer::Type::Tile) {
            sf::VertexArray layerVertexArray = TileMap::loadTileLayer(layer->getLayerAs<tmx::TileLayer>(), tileset, map.getTileCount(), map.getTileSize());
            playerMenuLayer.addLayerVertices(layer->getName(), layerVertexArray);
        }
    }

    menuMap.setPlayerMenuLayer(playerMenuLayer);
    return menuMap;
}

SceneMap MapLoader::loadSceneMap(TextureManager& textureManager, std::string sceneName) {
    SceneMap sceneMap;
    tmx::Map map;

    std::string sceneMapPath = AssetPath::getSceneMapPath(sceneName);
    if(!map.load(sceneMapPath)) {
        //TODO: exit the application after printing the error that the file couldn't be loaded
    }

    //TODO: this assumes that each scene is only going to have a single tileset
    tmx::Tileset tileset = map.getTilesets()[0];

    sceneMap.setTilesetImagePath(tileset.getImagePath());
    textureManager.loadTexture(sceneMap.getTilesetImagePath());
    sceneMap.setTileMapTexture(textureManager.getTexture(sceneMap.getTilesetImagePath()));

    //tile count and tile size
    sceneMap.setMapSizeInTiles(sf::Vector2u(map.getTileCount().x, map.getTileCount().y));
    sceneMap.setTileSize(sf::Vector2u(map.getTileSize().x, map.getTileSize().y));
    sceneMap.setMapSizeInPixels(sf::Vector2u(sceneMap.getMapSizeInTiles().x * sceneMap.getTileSize().x,
            sceneMap.getMapSizeInTiles().y * sceneMap.getTileSize().y));

    const auto& layers = map.getLayers();
    for(const auto& layer : layers) {
        if(layer->getType() == tmx::Layer::Type::Tile) {
            sf::VertexArray layerVertexArray = TileMap::loadTileLayer(layer->getLayerAs<tmx::TileLayer>(), tileset, map.getTileCount(), map.getTileSize());
            sceneMap.addVertices(layerVertexArray);
        } else if(layer->getType() == tmx::Layer::Type::Object) {
            sceneMap.loadObjectLayer(layer->getLayerAs<tmx::ObjectGroup>());
        } else {
            logger.logError("not supporting this type of layer yet");
        }
    }

    logger.logDebug("done loading tile map");
    return sceneMap;
}
