#include "../../../includes/ui/component/UIComponentManager.h"

Logger UIComponentManager::logger("UIComponentManager");

void UIComponentManager::drawToRenderTexture(sf::RenderTexture *renderTexture) {
    if(state == STATE_ACTIVE) {
        renderTexture->draw(playerMenuLayer);
    }
}

void UIComponentManager::updateComponentOriginPosition(sf::RenderTexture& renderTexture, sf::View& view) {
    sf::Vector2f viewCenter = view.getCenter();
    sf::Vector2f viewSize = view.getSize();

    //The menu maps are basically 320 x 180 textures, where everything is transparent EXCEPT for the menus that I drew
    //So within the "texture" the menu is placed in the right position, but the texture itself needs to be drawn like its a big 320x180 box
    sf::Vector2f position = sf::Vector2f(viewCenter.x - (viewSize.x/2), viewCenter.y - (viewSize.y/2));

    playerMenuLayer.updateMenuPositionsWithNewOriginPosition(renderTexture, position);
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
    if(playerMenuLayer.doesRootMenuHaveFocus()) {
        playerMenuLayer.closeRootMenu();
        closeMenu();
    } else {
        playerMenuLayer.closeCurrentMenuWithFocus();
    }
}

void UIComponentManager::onControllerMenuMoveEvent(MoveDirection direction) {
    if(state == STATE_ACTIVE) {
        playerMenuLayer.moveSelector(direction);
    }
}

void UIComponentManager::onControllerActionEvent() {
    if(state == STATE_ACTIVE) {
        //select something in the menu if this is active
        playerMenuLayer.selectMenuOption();
    }
}

void UIComponentManager::release(TextureManager& textureManager) {
    playerMenuLayer.release(textureManager); //NOTE: only needs to happen once, all menuLayers will share the same texture
}