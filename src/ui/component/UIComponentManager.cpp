#include "../../../includes/ui/component/UIComponentManager.h"

const std::string PLAYER_MENU_NAME = "player_menu";
Logger UIComponentManager::logger("UIComponentManager");

void UIComponentManager::initialize(std::shared_ptr<EventBus> eventBus, TextureManager& textureManager, sf::Font* font, float windowScale) {
    this->eventBus = eventBus;

    textureManager.loadTexture(AssetPath::MENU_SELECTOR_TEXTURE);
    this->playerMenuLayer = mapLoader.loadMenuLayerMap(textureManager, PLAYER_MENU_NAME);
    this->playerMenuLayer.initialize(textureManager.getTexture(AssetPath::MENU_SELECTOR_TEXTURE), font, windowScale);
}

void UIComponentManager::update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime) {
    switch(state) {
        case STATE_INACTIVE:
            break;
        case STATE_READY:
            updateComponentPositions(renderTexture, view);
            break;
        case STATE_ACTIVE:
            playerMenuLayer.update(renderTexture);
            break;
    }
}

void UIComponentManager::drawToRenderTexture(sf::RenderTexture *renderTexture) {
    if(state == STATE_ACTIVE) {
        renderTexture->draw(playerMenuLayer);
    }
}

void UIComponentManager::updateComponentPositions(sf::RenderTexture& renderTexture, sf::View& view) {
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    //The menu maps are basically 320 x 180 textures, where everything is transparent EXCEPT for the menus that I drew
    //So within the "texture" the menu is placed in the right position, but the texture itself needs to be drawn like its a big 320x180 box
    //I don't know if I like this, but I don't think theres a way to color the tiles without doing this. The concern is, will it be easy to put text in?
    sf::Vector2f position = sf::Vector2f(viewCenter.x - (viewSize.x/2), viewCenter.y - (viewSize.y/2));
    playerMenuLayer.setMenuLayerPosition(position, renderTexture);

    state = STATE_ACTIVE;
}

void UIComponentManager::closeMenu() {
    if(state == STATE_ACTIVE || state == STATE_READY) {
        state = STATE_INACTIVE;
        eventBus->publish(new CloseMenuEvent());
    }
}

bool UIComponentManager::isMenuActive() {
    return !(state == STATE_INACTIVE);
}

void UIComponentManager::resetForNewScene() {
    closeMenu();
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

void UIComponentManager::onControllerMenuMoveEvent(MoveDirection direction) {
    playerMenuLayer.moveSelector(direction);
}

void UIComponentManager::onControllerActionEvent() {
    //select something in the menu if this is active
}

void UIComponentManager::release(TextureManager& textureManager) {
    textureManager.releaseTexture(AssetPath::MENU_SELECTOR_TEXTURE);
//    menuMap.release(textureManager); //TODO: need to release the MenuLayer and make sure the texture its using is released with it
    //TODO: should probably release the menu selector texture in MenuLayer too
}