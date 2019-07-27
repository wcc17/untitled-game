#include "../../../includes/ui/component/UIComponentManager.h"

const std::string SCENE_NAME = "menu";
Logger UIComponentManager::logger("UIComponentManager");

void UIComponentManager::initialize(std::shared_ptr<EventBus> eventBus, TextureManager& textureManager) {
    this->eventBus = eventBus;
    this->menuMap = mapLoader.loadMenuMap(textureManager, SCENE_NAME); //TODO: do i need to keep the menuMap around here? Not as necessary as in Scene
    this->playerMenuLayer = menuMap.getPlayerMenuLayer();
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
        renderTexture->draw(playerMenuLayer);
    }
}

void UIComponentManager::updateComponentPositions(sf::RenderWindow* window, sf::View& view) {
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    //The menu maps are basically 320 x 180 textures, where everything is transparent EXCEPT for the menus that I drew
    //So within the "texture" the menu is placed in the right position, but the texture itself needs to be drawn like its a big 320x180 box
    //I don't know if I like this, but I don't think theres a way to color the tiles without doing this. The concern is, will it be easy to put text in?
    sf::Vector2f position = sf::Vector2f(viewCenter.x - (viewSize.x/2), viewCenter.y - (viewSize.y/2));
    playerMenuLayer.setPosition(position);

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
    menuMap.release(textureManager);
}