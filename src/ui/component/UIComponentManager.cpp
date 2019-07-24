#include "../../../includes/ui/component/UIComponentManager.h"

void UIComponentManager::initialize(std::shared_ptr<EventBus> eventBus, TextureManager& textureManager) {
    this->eventBus = eventBus;

    std::string textureFileName = AssetPath::getUIComponentAssetPath("player_menu");
    textureManager.loadTexture(textureFileName);
    playerMenuComponent.initialize("player_menu", textureManager.getTexture(textureFileName));
    playerMenuComponent.setPosition(150, 0);
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
    float x = view.getCenter().x + (view.getSize().x / 2) - playerMenuComponent.getGlobalBounds().width - (5); //TODO: magic numbers
    float y = view.getCenter().y - (view.getSize().y / 2) + ((view.getSize().y - playerMenuComponent.getGlobalBounds().height) / 2); //TODO: magic numbers
    playerMenuComponent.setPosition(x, y);

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
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(playerMenuComponent.getAssetName()));
}