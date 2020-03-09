#include "../../../includes/ui/manager/OverworldUIManager.h"

void OverworldUIManager::initializeComponents(
        TextureManager &textureManager,
        float windowScale,
        sf::Font *font,
        std::string sceneName) {
    textureManager.loadTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR));

    dialogueMenuComponent = uiComponentInitializer.initializeDialogueMenuComponent(textureManager, windowScale, font);
    startMenuComponent = uiComponentInitializer.initializeStartMenuComponent(textureManager, windowScale, font);
    partyMenuComponent = uiComponentInitializer.initializePartyMenuComponent(textureManager, windowScale, font);

    //TODO: I need four of these and they're specific to battle menu. Need to be able to initialize these components outside of here or at least conditionally depending on what scene we're in. BattleUIManager and OverworldUIManager would probably be cool
//    battleChoiceMenuComponent = uiComponentInitializer.initializeBattleMenuComponent(textureManager, windowScale, font, true, 0);

    std::vector<DialogueEvent> entityDialogueEvents = xmlManager.loadEntityDialogueForScene(sceneName); //TODO: need to see how this works for the battle scene
    dialogueMenuComponent.setEntityDialogueEvents(entityDialogueEvents);
}

void OverworldUIManager::openDialogue(std::string dialogueTextAssetName) {
    activeMenuComponent = &dialogueMenuComponent;
    activeMenuComponent->openDialogue(dialogueTextAssetName);
}

void OverworldUIManager::openMenu(UIComponentType menuTypeToOpen) {
    switch (menuTypeToOpen) {
        case PARTY_MENU:
            activeMenuComponent = &partyMenuComponent;
            break;
        case START_MENU:
            activeMenuComponent = &startMenuComponent;
            break;
        case BATTLE_CHARACTER_CHOICES_MENU:
            break;
        default:
            break;
    }
}

void OverworldUIManager::handleControllerMenuButtonPressed() {
    if(!isAnyMenuOpen()) {
        openMenu(UIComponentType::START_MENU);
        eventBus->publish(new PauseGameEvent());
//        activeMenuComponent->handleControllerMenuButtonPressed(eventBus);
    }
}

void OverworldUIManager::handleControllerActionButtonPressed() {
//    if (activeMenuComponent != nullptr) {
//        activeMenuComponent->handleControllerActionButtonPressed(eventBus);
//    }
}

void OverworldUIManager::handleControllerCancelButtonPressed() {
//    if (activeMenuComponent != nullptr) {
//        activeMenuComponent->handleControllerCancelButtonPressed(eventBus);
//    }

    closeCurrentMenuOrDialogue();
    eventBus->publish(new UnPauseGameEvent());
}

void OverworldUIManager::handleControllerMenuMoveButtonPressed(MoveDirection direction) {
    if (activeMenuComponent != nullptr) {
        activeMenuComponent->handleControllerMenuMoveButtonPressed(direction);
    }
}

void OverworldUIManager::release(TextureManager &textureManager) {
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR));
    UIManager::release(textureManager);
}
