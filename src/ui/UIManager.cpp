#include "../../includes/ui/UIManager.h"

void UIManager::initialize(std::shared_ptr<EventBus> eventBus, TextureManager& textureManager, sf::Font* font, sf::Vector2u windowSize, sf::Vector2f defaultWindowSize) {
    this->eventBus = eventBus;

    float windowScale = (windowSize.x / defaultWindowSize.x); //assuming aspect ratio is 16:9 I think
    textureManager.loadTexture(AssetPath::DIALOGUE_BOX_TEXTURE);

    dialogueManager.initialize(eventBus, textureManager.getTexture(AssetPath::DIALOGUE_BOX_TEXTURE), font, windowScale);
    uiComponentManager.initialize(eventBus, textureManager);

    eventBus->subscribe(this, &UIManager::onControllerMenuEvent);
    eventBus->subscribe(this, &UIManager::onControllerActionEvent);
    eventBus->subscribe(this, &UIManager::onOpenDialogueEvent);
    eventBus->subscribe(this, &UIManager::onControllerCancelEvent);
}

void UIManager::update(sf::RenderWindow* window, sf::View& view, sf::Time deltaTime) {
    uiComponentManager.update(window, view, deltaTime);
    dialogueManager.update(window, view, deltaTime);
}

void UIManager::drawToRenderTexture(sf::RenderTexture* renderTexture) {
    uiComponentManager.drawToRenderTexture(renderTexture);
    dialogueManager.drawToRenderTexture(renderTexture);
}

void UIManager::resetOnNewScene(std::vector<DialogueEvent> entityDialogueEvents) {
    dialogueManager.setEntityDialogueEvents(entityDialogueEvents);
    resetMenu();
}

void UIManager::resetMenu() {
    uiComponentManager.resetForNewScene();
}

void UIManager::onControllerMenuEvent(ControllerMenuEvent* event) {
    if(!dialogueManager.isDialogueActive()) {
        uiComponentManager.onControllerMenuEvent();
    }
}

void UIManager::onControllerActionEvent(ControllerActionEvent* event) {
    dialogueManager.onControllerActionEvent();
}

void UIManager::onControllerCancelEvent(ControllerCancelEvent* event) {
    uiComponentManager.onControllerCancelEvent();
}

void UIManager::onOpenDialogueEvent(OpenDialogueEvent* event) {
    if(!uiComponentManager.isMenuActive()) {
        dialogueManager.onOpenDialogueEvent(event);
    }
}

void UIManager::release(TextureManager& textureManager) {
    //TODO: unsubscribe from eventBus
    dialogueManager.release(textureManager);
    uiComponentManager.release(textureManager);
}