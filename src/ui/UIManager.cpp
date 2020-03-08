#include "../../includes/ui/UIManager.h"

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

void UIManager::initializeComponents(
        TextureManager &textureManager,
        float windowScale,
        sf::Font *font,
        std::string sceneName) {
    textureManager.loadTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR));

    dialogueMenuComponent = uiComponentInitializer.initializeDialogueMenuComponent(textureManager, eventBus, windowScale, font);
    startMenuComponent = uiComponentInitializer.initializeStartMenuComponent(textureManager, eventBus, windowScale, font);
    partyMenuComponent = uiComponentInitializer.initializePartyMenuComponent(textureManager, eventBus, windowScale, font);

    //TODO: I need four of these and they're specific to battle menu. Need to be able to initialize these components outside of here or at least conditionally depending on what scene we're in. BattleUIManager and OverworldUIManager would probably be cool
    battleChoiceMenuComponent = uiComponentInitializer.initializeBattleMenuComponent(textureManager, eventBus, windowScale, font, true, 0);

    std::vector<DialogueEvent> entityDialogueEvents = xmlManager.loadEntityDialogueForScene(sceneName); //TODO: need to see how this works for the battle scene
    dialogueMenuComponent.setEntityDialogueEvents(entityDialogueEvents);
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

void UIManager::openDialogue(std::string dialogueTextAssetName) {
    activeMenuComponent = &dialogueMenuComponent;
    activeMenuComponent->openDialogue(dialogueTextAssetName);
}

void UIManager::openMenu(UIComponentType menuTypeToOpen) {
    switch (menuTypeToOpen) {
        case PARTY_MENU:
            activeMenuComponent = &partyMenuComponent;
            break;
        case START_MENU:
            activeMenuComponent = &startMenuComponent;
            break;
        case BATTLE_CHARACTER_CHOICES_MENU:
            activeMenuComponent = &battleChoiceMenuComponent;
        default:
            break;
    }
}

void UIManager::closeCurrentMenuOrDialogue() {
    activeMenuComponent = nullptr;
}

void UIManager::handleControllerMenuButtonPressed() {
    if (activeMenuComponent == nullptr) {
        activeMenuComponent = &startMenuComponent;
        eventBus->publish(new OpenMenuEvent(UIComponentType::START_MENU));
    }
}

void UIManager::handleControllerActionButtonPressed() {
    if (activeMenuComponent != nullptr) {
        //TODO: open the menu thats stored in the "opensTo" variable on the selected menu option. Probably will publish an OpenMenuEvent like handleControllerMenuButtonPressed
        //TODO: how to decide when to publish this event?
//        publishOnlyEventBus->publish(new OpenMenuEvent(activeMenuComponent->getNextMenuType()));

        activeMenuComponent->handleControllerActionButtonPressed();
    }
}

void UIManager::handleControllerCancelButtonPressed() {
    if (activeMenuComponent != nullptr) {
        eventBus->publish(new CloseMenuEvent());
    }
}

void UIManager::handleControllerMenuMoveButtonPressed(MoveDirection direction) {
    if (activeMenuComponent != nullptr) {
        activeMenuComponent->handleControllerMenuMoveButtonPressed(direction);
    }
}

void UIManager::release(TextureManager &textureManager) {
    uiComponentInitializer.release(textureManager);
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR));
}