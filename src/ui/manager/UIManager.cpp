#include "../../../includes/ui/manager/UIManager.h"

void UIManager::initialize(
        std::shared_ptr<EventBus> eventBus,
        TextureManager &textureManager,
        sf::Font *font,
        sf::Vector2u windowSize,
        sf::Vector2f defaultWindowSize,
        std::string sceneName) {
    this->eventBus = eventBus;
    float windowScale = (windowSize.x / defaultWindowSize.x); //assuming aspect ratio is 16:9 I think
    initializeComponents(textureManager, windowScale, font, sceneName);
}

void UIManager::update(
        sf::RenderTexture &renderTexture,
        sf::View &view,
        sf::Time deltaTime) {
    if (activeMenuComponent != nullptr) {
        activeMenuComponent->update(renderTexture, view, deltaTime);
    }
}

void UIManager::drawToRenderTexture(sf::RenderTexture &renderTexture) const {
    if (activeMenuComponent != nullptr) {
        activeMenuComponent->drawToRenderTexture(&renderTexture);
    }
}

void UIManager::closeCurrentMenuOrDialogue() {
    activeMenuComponent = nullptr;
}

bool UIManager::isAnyMenuOpen() {
    return (activeMenuComponent != nullptr);
}

bool UIManager::checkActiveComponentActionFinished() {
    return activeMenuComponent->componentActionIsFinished();
}

void UIManager::release(TextureManager &textureManager) {
    uiComponentInitializer.release(textureManager);
}