#include "../../includes/ui/UIManager.h"

void UIManager::initialize(std::shared_ptr<EventBus> eventBus, TextureManager& textureManager, sf::Font* font, sf::Vector2u windowSize, sf::Vector2f defaultWindowSize) {
    this->eventBus = eventBus;
    dialogueManager.initialize(eventBus);

    float windowScale = (windowSize.x / defaultWindowSize.x); //assuming aspect ratio is 16:9 I think
    initializeComponents(textureManager, windowScale, font);

    eventBus->subscribe(this, &UIManager::onControllerMenuEvent);
    eventBus->subscribe(this, &UIManager::onControllerActionEvent);
    eventBus->subscribe(this, &UIManager::onOpenDialogueEvent);
    eventBus->subscribe(this, &UIManager::onCloseDialogueEvent);
    eventBus->subscribe(this, &UIManager::onControllerCancelEvent);
    eventBus->subscribe(this, &UIManager::onControllerMenuMoveEvent);
}

void UIManager::initializeComponents(TextureManager& textureManager, float windowScale, sf::Font* font) {
    std::string menuSelectorPath = AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR);
    textureManager.loadTexture(menuSelectorPath);
    menuSelectorSprite.setTexture(*textureManager.getTexture(menuSelectorPath));

    dialogueMenuComponent = uiComponentInitializer.initializeDialogueMenuComponent(textureManager, windowScale, font);
    startMenuComponent = uiComponentInitializer.initializeStartMenuComponent(textureManager, windowScale, font, menuSelectorSprite.getGlobalBounds());
    partyMenuComponent = uiComponentInitializer.initializePartyMenuComponent(textureManager, windowScale, font, menuSelectorSprite.getGlobalBounds());
}

//TODO: state machine instead of switch statements
void UIManager::update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime) {
    switch(state) {
        case UIStateType::STATE_START_MENU: {
            startMenuComponent.updatePositionForView(renderTexture, view);
            updateSelectorPositionBasedOnMenuComponent(startMenuComponent);
            break;
        }
        case UIStateType::STATE_PARTY_MENU: {
            partyMenuComponent.updatePositionForView(renderTexture, view);
            updateSelectorPositionBasedOnMenuComponent(partyMenuComponent);
            break;
        }
        case UIStateType::STATE_DIALOGUE: {
            dialogueManager.update(renderTexture, view, deltaTime);
            dialogueMenuComponent.updatePositionForView(renderTexture, view);
            dialogueMenuComponent.updateMenuOption(dialogueManager.getStringToDraw());
            break;
        }
    }

}

void UIManager::drawToRenderTexture(sf::RenderTexture* renderTexture) {
    switch(state) {
        case UIStateType::STATE_START_MENU:
            startMenuComponent.drawToRenderTexture(renderTexture);
            renderTexture->draw(menuSelectorSprite);
            break;
        case UIStateType ::STATE_PARTY_MENU:
            partyMenuComponent.drawToRenderTexture(renderTexture);
            renderTexture->draw(menuSelectorSprite);
        case UIStateType::STATE_DIALOGUE:
            dialogueMenuComponent.drawToRenderTexture(renderTexture);
            break;
    }
}

void UIManager::onControllerMenuEvent(ControllerMenuEvent* event) {
    switch(state) {
        case UIStateType::STATE_NONE:
            state = UIStateType::STATE_START_MENU;
            eventBus->publish(new OpenMenuEvent());
            break;
        default:
            break;
    }
}

void UIManager::onControllerActionEvent(ControllerActionEvent* event) {
    switch(state) {
        case UIStateType::STATE_DIALOGUE:
            dialogueManager.onControllerActionEvent();
            break;
        case UIStateType::STATE_START_MENU:
            if(startMenuComponent.getActiveMenuOptionNextMenu() == UIComponentType::PARTY_MENU) {
                state = UIStateType ::STATE_PARTY_MENU;
            }
            break;
        default:
            break;
    }
}

void UIManager::onControllerCancelEvent(ControllerCancelEvent* event) {
    switch(state) {
        case UIStateType::STATE_START_MENU:
        case UIStateType::STATE_PARTY_MENU:
            state = UIStateType::STATE_NONE;
            eventBus->publish(new CloseMenuEvent());
            break;
    }
}

void UIManager::onOpenDialogueEvent(OpenDialogueEvent* event) {
    switch(state) {
        case UIStateType::STATE_NONE:
            state = UIStateType::STATE_DIALOGUE;
            dialogueManager.onOpenDialogueEvent(event);
            break;
        default:
            break;
    }
}

void UIManager::onCloseDialogueEvent(CloseDialogueEvent *event) {
    switch(state) {
        case UIStateType::STATE_DIALOGUE:
            state = UIStateType::STATE_NONE;
        default:
            break;
    }
}

void UIManager::onControllerMenuMoveEvent(ControllerMenuMoveEvent* event) {
    switch(state) {
        case UIStateType::STATE_NONE:
            break;
        case UIStateType::STATE_DIALOGUE:
            break;
        case UIStateType::STATE_START_MENU:
            startMenuComponent.changeActiveMenuOption(event->direction);
            break;
        case UIStateType ::STATE_PARTY_MENU:
            partyMenuComponent.changeActiveMenuOption(event->direction);
            break;
    }
}

void UIManager::resetOnNewScene(std::vector<DialogueEvent> entityDialogueEvents) {
    dialogueManager.setEntityDialogueEvents(entityDialogueEvents);
}

void UIManager::updateSelectorPositionBasedOnMenuComponent(MenuComponent menuComponent) {
    sf::Vector2f selectorDimensions = sf::Vector2f(
            menuSelectorSprite.getGlobalBounds().width,
            menuSelectorSprite.getGlobalBounds().height);
    menuSelectorSprite.setPosition(
            menuComponent.getSelectorPositionBasedOnSelectedMenuOption(selectorDimensions));
}

void UIManager::release(TextureManager& textureManager) {
    //TODO: unsubscribe from eventBus
    uiComponentInitializer.release(textureManager);
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR));
}