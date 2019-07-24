#include "../../../includes/ui/component/UIComponentManager.h"

void UIComponentManager::initialize(TextureManager& textureManager) {
    std::string textureFileName = AssetPath::getUIComponentAssetPath("player_menu");
    textureManager.loadTexture(textureFileName);
    playerMenuComponent.initialize("player_menu", textureManager.getTexture(textureFileName));
    playerMenuComponent.setPosition(150, 0);
}

void UIComponentManager::update(sf::RenderWindow* window, sf::View& view, sf::Time deltaTime) {
    if(menuIsActive) {
        if(!positionsSet) {
            updateComponentPositions(window, view);
        }
    }
}

void UIComponentManager::drawToRenderTexture(sf::RenderTexture *renderTexture) {
    if(menuIsActive) {
        renderTexture->draw(playerMenuComponent);
    }
}

bool UIComponentManager::isMenuActive() {
    return menuIsActive;
}

void UIComponentManager::updateComponentPositions(sf::RenderWindow* window, sf::View& view) {
    float x = view.getCenter().x + (view.getSize().x / 2) - playerMenuComponent.getGlobalBounds().width - (5); //TODO: magic numbers
    float y = view.getCenter().y - (view.getSize().y / 2) + ((view.getSize().y - playerMenuComponent.getGlobalBounds().height) / 2); //TODO: magic numbers
    playerMenuComponent.setPosition(x, y);

    positionsSet = true;
}

void UIComponentManager::onControllerMenuEvent() {
    menuIsActive = true;
}

void UIComponentManager::onControllerEscapeEvent() {
    menuIsActive = false;
    positionsSet = false;
}

void UIComponentManager::onControllerActionEvent() {
    //select something in the menu if this is active
}

void UIComponentManager::release(TextureManager& textureManager) {
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(playerMenuComponent.getAssetName()));
}