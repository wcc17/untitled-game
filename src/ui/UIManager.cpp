#include "../../includes/ui/UIManager.h"

void UIManager::initialize(std::shared_ptr<EventBus> eventBus, TextureManager& textureManager, sf::Font* font, sf::Vector2u windowSize, sf::Vector2f defaultWindowSize) {
    this->eventBus = eventBus;

    float windowScale = (windowSize.x / defaultWindowSize.x); //assuming aspect ratio is 16:9 I think
    initializeComponents(textureManager, windowScale, font);

    eventBus->subscribe(this, &UIManager::onControllerMenuEvent);
    eventBus->subscribe(this, &UIManager::onControllerActionEvent);
    eventBus->subscribe(this, &UIManager::onOpenDialogueEvent);
    eventBus->subscribe(this, &UIManager::onCloseDialogueEvent);
    eventBus->subscribe(this, &UIManager::onControllerCancelEvent);
    eventBus->subscribe(this, &UIManager::onControllerMenuMoveEvent);
}

void UIManager::update(sf::RenderTexture& renderTexture, sf::View& view, sf::Time deltaTime) {
    switch(state) {
        case UIState::STATE_MENU: {
            sf::Vector2f selectorDimensions = sf::Vector2f(
                    menuSelectorSprite.getGlobalBounds().width,
                    menuSelectorSprite.getGlobalBounds().height);
            menuSelectorSprite.setPosition(
                    startMenuComponent.getSelectorPositionBasedOnSelectedMenuOption(selectorDimensions));
            startMenuComponent.updatePositionForView(renderTexture, view);
            break;
        }
        case UIState::STATE_DIALOGUE: {
            dialogueManager.update(renderTexture, view, deltaTime);
            dialogueMenuComponent.updatePositionForView(renderTexture, view);
            dialogueMenuComponent.updateMenuOption(dialogueManager.getStringToDraw());
            break;
        }
    }

}

void UIManager::drawToRenderTexture(sf::RenderTexture* renderTexture) {
    switch(state) {
        case UIState::STATE_MENU:
            startMenuComponent.drawToRenderTexture(renderTexture);
            renderTexture->draw(menuSelectorSprite);
            break;
        case UIState::STATE_DIALOGUE:
            dialogueMenuComponent.drawToRenderTexture(renderTexture);
            break;
    }
}

void UIManager::onControllerMenuEvent(ControllerMenuEvent* event) {
    switch(state) {
        case UIState::STATE_NONE:
            state = UIState::STATE_MENU;
            eventBus->publish(new OpenMenuEvent());
            break;
        default:
            break;
    }
}

void UIManager::onControllerActionEvent(ControllerActionEvent* event) {
    dialogueManager.onControllerActionEvent();
}

void UIManager::onControllerCancelEvent(ControllerCancelEvent* event) {
    switch(state) {
        case UIState::STATE_MENU:
            state = UIState::STATE_NONE;
            eventBus->publish(new CloseMenuEvent());
            break;
    }
}

void UIManager::onOpenDialogueEvent(OpenDialogueEvent* event) {
    switch(state) {
        case UIState::STATE_NONE:
            state = UIState::STATE_DIALOGUE;
            dialogueManager.onOpenDialogueEvent(event);
            break;
        default:
            break;
    }
}

void UIManager::onCloseDialogueEvent(CloseDialogueEvent *event) {
    switch(state) {
        case UIState::STATE_DIALOGUE:
            state = UIState::STATE_NONE;
        default:
            break;
    }
}

void UIManager::onControllerMenuMoveEvent(ControllerMenuMoveEvent* event) {
    switch(state) {
        case UIState::STATE_NONE:
            break;
        case UIState::STATE_DIALOGUE:
            break;
        case UIState::STATE_MENU:
            startMenuComponent.changeActiveMenuOption(event->direction);
            break;
    }
}

void UIManager::resetOnNewScene(std::vector<DialogueEvent> entityDialogueEvents) {
    dialogueManager.setEntityDialogueEvents(entityDialogueEvents);
}

void UIManager::release(TextureManager& textureManager) {
    //TODO: unsubscribe from eventBus
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(DIALOGUE_BOX));
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(START_MENU));
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(MENU_SELECTOR));
}


//TODO: can these be initialized somewhere else?
void UIManager::initializeComponents(TextureManager& textureManager, float windowScale, sf::Font* font) {
    std::string menuSelectorPath = AssetPath::getUIComponentAssetPath(MENU_SELECTOR);
    textureManager.loadTexture(menuSelectorPath);
    menuSelectorSprite.setTexture(*textureManager.getTexture(menuSelectorPath));

    initializeDialogueMenuComponent(textureManager, windowScale, font);
    initializeStartMenuComponent(textureManager, windowScale, font);
}

void UIManager::initializeDialogueMenuComponent(TextureManager& textureManager, float windowScale, sf::Font* font) {
    std::string dialogueBoxAssetPath = AssetPath::getUIComponentAssetPath(DIALOGUE_BOX);
    textureManager.loadTexture(dialogueBoxAssetPath);
    dialogueMenuComponent.initialize(
            font,
            windowScale,
            DIALOGUE_BOX,
            ObjectType::MENU,
            textureManager.getTexture(dialogueBoxAssetPath),
            ScreenPosition::BOTTOM_LEFT,
            sf::Vector2f(0, 0));

    MenuOptionComponent textOptionComponent;
    std::string displayText = "";
    std::string opensToMenu = "";
    textOptionComponent.initialize(std::to_string(0), ObjectType::MENU_OPTION, 0, displayText, opensToMenu);
    dialogueMenuComponent.addMenuOption(textOptionComponent);

    //TODO: I don't want the dialogue box texture to be handled in dialogueManager
    dialogueManager.initialize(eventBus, textureManager.getTexture(dialogueBoxAssetPath), font, windowScale);
}

void UIManager::initializeStartMenuComponent(TextureManager& textureManager, float windowScale, sf::Font* font) {
    std::string startMenuAssetPath = AssetPath::getUIComponentAssetPath(START_MENU);
    textureManager.loadTexture(startMenuAssetPath);
    startMenuComponent.initialize(
            font,
            windowScale,
            START_MENU,
            ObjectType::MENU,
            textureManager.getTexture(startMenuAssetPath),
            ScreenPosition::TOP_RIGHT,
            sf::Vector2f(menuSelectorSprite.getGlobalBounds().width, 0));

    initializeStartMenuComponentOption(0, "Party", "");
    initializeStartMenuComponentOption(1, "Items", "");
    initializeStartMenuComponentOption(2, "Skills", "");
    initializeStartMenuComponentOption(3, "Options", "");
    initializeStartMenuComponentOption(4, "Save", "");
    initializeStartMenuComponentOption(5, "Exit", "");
}

void UIManager::initializeStartMenuComponentOption(int index, std::string displayText, std::string opensToMenu) {
    MenuOptionComponent menuOption;
    menuOption.initialize(std::to_string(index), ObjectType::MENU_OPTION, index, displayText, opensToMenu);
    startMenuComponent.addMenuOption(menuOption);
}