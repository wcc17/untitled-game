#include "../../../includes/ui/component/UIComponentManager.h"

const std::string SCENE_NAME = "menu";
Logger UIComponentManager::logger("UIComponentManager");

void UIComponentManager::initialize(std::shared_ptr<EventBus> eventBus, TextureManager& textureManager) {
    this->eventBus = eventBus;
    loadMenuMap(textureManager);
}

void UIComponentManager::loadMenuMap(TextureManager& textureManager) {
    tmx::Map map;

    std::string sceneMapPath = AssetPath::getSceneMapPath(SCENE_NAME);
    if(!map.load(sceneMapPath)) {
        //TODO: exit the application after printing the error that the file couldn't be loaded
    }

    tmx::Tileset tileset = map.getTilesets()[0];

    this->tilesetImagePath = tileset.getImagePath();
    textureManager.loadTexture(tilesetImagePath);
    this->tileMapTexture = textureManager.getTexture(tilesetImagePath);

    //load object layers first to get the menus initialized
    const auto& layers = map.getLayers();
    for(const auto& layer : layers) {
        if(layer->getType() == tmx::Layer::Type::Object) {
            menuObjectMap.loadObjectLayer(layer->getLayerAs<tmx::ObjectGroup>());
        }
    }

    playerMenuComponent = menuObjectMap.getPlayerMenuComponent();

    //load tile layers and assign the vertices to each menu where appropriate
    std::map<std::string, std::vector<sf::VertexArray>> vertexArrayMap;
    for(const auto& layer : layers) {
        if(layer->getType() == tmx::Layer::Type::Tile) {
            tileMap.loadTileLayer(layer->getLayerAs<tmx::TileLayer>(), tileset, map.getTileCount(), map.getTileSize());
            vertexArrayMap.insert(std::make_pair(layer->getName(), tileMap.getVertices()));
        }
    }


    playerMenuComponent.setComponentTexture(tileMapTexture, vertexArrayMap.at(playerMenuComponent.getName()));
}

void UIComponentManager::update(sf::RenderWindow* window, sf::View& view, sf::Time deltaTime) {
    switch(state) {
        case STATE_INACTIVE:
            break;
        case STATE_READY:
            updateComponentPositions(window, view);
            break;
        case STATE_ACTIVE:
            break;
    }
}

void UIComponentManager::drawToRenderTexture(sf::RenderTexture *renderTexture) {
    if(state == STATE_ACTIVE) {
        renderTexture->draw(playerMenuComponent);
    }
}

void UIComponentManager::updateComponentPositions(sf::RenderWindow* window, sf::View& view) {
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    //The menu maps are basically 320 x 180 textures, where everything is transparent EXCEPT for the menus that I drew
    //So within the "texture" the menu is placed in the right position, but the texture itself needs to be drawn like its a big 320x180 box
    //I don't know if I like this, but I don't think theres a way to color the tiles without doing this. The concern is, will it be easy to put text in?
    sf::Vector2f whyDoesThisWork = sf::Vector2f(viewCenter.x - viewSize.x/2, viewCenter.y - viewSize.y/2);
    playerMenuComponent.setPosition(whyDoesThisWork);

    state = STATE_ACTIVE;
}

void UIComponentManager::onControllerMenuEvent() {
    if(state == STATE_INACTIVE) {
        state = STATE_READY;
        eventBus->publish(new OpenMenuEvent());
    }
}

void UIComponentManager::onControllerCancelEvent() {
    closeMenu();
}

void UIComponentManager::closeMenu() {
    if(state == STATE_ACTIVE || state == STATE_READY) {
        state = STATE_INACTIVE;
        eventBus->publish(new CloseMenuEvent());
    }
}

void UIComponentManager::onControllerActionEvent() {
    //select something in the menu if this is active
}

bool UIComponentManager::isMenuActive() {
    return !(state == STATE_INACTIVE);
}

void UIComponentManager::resetForNewScene() {
    closeMenu();

}

void UIComponentManager::release(TextureManager& textureManager) {
    textureManager.releaseTexture(tilesetImagePath);
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(playerMenuComponent.getName()));
}