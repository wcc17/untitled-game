#include "../../includes/ui/UIManager.h"

void UIManager::initialize(std::shared_ptr<EventBus> eventBus, TextureManager& textureManager, sf::Font* font, sf::Vector2u windowSize, sf::Vector2f defaultWindowSize) {
    this->eventBus = eventBus;

    float windowScale = (windowSize.x / defaultWindowSize.x); //assuming aspect ratio is 16:9 I think
    initializeComponents(textureManager, windowScale, font);

    eventBus->subscribe(this, &UIManager::onOpenDialogueEvent);
    eventBus->subscribe(this, &UIManager::onCloseDialogueEvent);
    eventBus->subscribe(this, &UIManager::onOpenMenuEvent);
    eventBus->subscribe(this, &UIManager::onCloseMenuEvent);
    eventBus->subscribe(this, &UIManager::onControllerActionEvent);
    eventBus->subscribe(this, &UIManager::onControllerMenuEvent);
    eventBus->subscribe(this, &UIManager::onControllerCancelEvent);
    eventBus->subscribe(this, &UIManager::onControllerMenuMoveEvent);
}

void UIManager::initializeComponents(TextureManager& textureManager, float windowScale, sf::Font* font) {
    textureManager.loadTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR));

    dialogueMenuComponent = uiComponentInitializer.initializeDialogueMenuComponent(textureManager, eventBus, windowScale, font);
    startMenuComponent = uiComponentInitializer.initializeStartMenuComponent(textureManager, eventBus, windowScale, font);
    partyMenuComponent = uiComponentInitializer.initializePartyMenuComponent(textureManager, eventBus, windowScale, font);
}

void UIManager::update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime) {
    if(activeMenuComponent != nullptr) {
        activeMenuComponent->update(renderTexture, view, deltaTime);
    }
}

void UIManager::drawToRenderTexture(sf::RenderTexture* renderTexture) {
    if(activeMenuComponent != nullptr) {
        activeMenuComponent->drawToRenderTexture(renderTexture);
    }
}

void UIManager::onOpenDialogueEvent(OpenDialogueEvent* event) {
    activeMenuComponent = &dialogueMenuComponent;
    activeMenuComponent->onOpenDialogueEvent(event);
}

void UIManager::onOpenMenuEvent(OpenMenuEvent* event) {
    activeMenuComponent = &startMenuComponent;
}

void UIManager::onCloseDialogueEvent(CloseDialogueEvent *event) {
    activeMenuComponent = nullptr;
}

void UIManager::onCloseMenuEvent(CloseMenuEvent *event) {
    activeMenuComponent = nullptr;
}

void UIManager::onControllerMenuEvent(ControllerMenuEvent* event){
    if(activeMenuComponent != nullptr) {
        activeMenuComponent->onControllerMenuEvent(event);
    } else {
        activeMenuComponent = &startMenuComponent;
        activeMenuComponent->onControllerMenuEvent(event);
    }
}

void UIManager::onControllerActionEvent(ControllerActionEvent* event) {
    if(activeMenuComponent != nullptr) {
        activeMenuComponent->onControllerActionEvent(event);
    }
}

void UIManager::onControllerCancelEvent(ControllerCancelEvent* event) {
    if(activeMenuComponent != nullptr) {
        activeMenuComponent->onControllerCancelEvent(event);
    }
}

void UIManager::onControllerMenuMoveEvent(ControllerMenuMoveEvent* event) {
    if(activeMenuComponent != nullptr) {
        activeMenuComponent->onControllerMenuMoveEvent(event);
    }
}

void UIManager::resetOnNewScene(std::vector<DialogueEvent> entityDialogueEvents) {
    dialogueMenuComponent.setEntityDialogueEvents(entityDialogueEvents);
}

void UIManager::release(TextureManager& textureManager) {
    //TODO: unsubscribe from eventBus
    uiComponentInitializer.release(textureManager);
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR));
}