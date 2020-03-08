#include "../../includes/ui/UIComponentInitializer.h"

DialogueMenuComponent UIComponentInitializer::initializeDialogueMenuComponent(
        TextureManager& textureManager,
        std::shared_ptr<EventBus> eventBus,
        float windowScale,
        sf::Font* font) {
    DialogueMenuComponent dialogueMenuComponent;

    std::string dialogueBoxAssetPath = AssetPath::getUIComponentAssetPath(UIComponentType::DIALOGUE_MENU);
    textureManager.loadTexture(dialogueBoxAssetPath);
    dialogueMenuComponent.initialize(
            eventBus,
            font,
            windowScale,
            textureManager.getTexture(dialogueBoxAssetPath),
            ScreenPosition::BOTTOM_LEFT);

    MenuOptionComponent textOptionComponent;
    std::string displayText = "";
    textOptionComponent.initialize(0, displayText, UIComponentType::NO_COMPONENT_TYPE);
    dialogueMenuComponent.addMenuOption(textOptionComponent);

    return dialogueMenuComponent;
}

MenuWithSelectorComponent UIComponentInitializer::initializeStartMenuComponent(
        TextureManager& textureManager,
        std::shared_ptr<EventBus> eventBus,
        float windowScale,
        sf::Font* font) {
    MenuWithSelectorComponent startMenuComponent;

    std::string startMenuAssetPath = AssetPath::getUIComponentAssetPath(UIComponentType::START_MENU);
    textureManager.loadTexture(startMenuAssetPath);
    startMenuComponent.initialize(
            eventBus,
            font,
            windowScale,
            textureManager.getTexture(startMenuAssetPath),
            textureManager.getTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR)),
            ScreenPosition::TOP_RIGHT);

    initializeMenuOptionComponent(0, "Party", UIComponentType::PARTY_MENU, startMenuComponent);
    initializeMenuOptionComponent(1, "Items", UIComponentType::NO_COMPONENT_TYPE, startMenuComponent);
    initializeMenuOptionComponent(2, "Skills", UIComponentType::NO_COMPONENT_TYPE, startMenuComponent);
    initializeMenuOptionComponent(3, "Options", UIComponentType::NO_COMPONENT_TYPE, startMenuComponent);
    initializeMenuOptionComponent(4, "Save", UIComponentType::NO_COMPONENT_TYPE, startMenuComponent);
    initializeMenuOptionComponent(5, "Exit", UIComponentType::NO_COMPONENT_TYPE, startMenuComponent);

    return startMenuComponent;
}

MenuWithSelectorComponent UIComponentInitializer::initializePartyMenuComponent(
        TextureManager& textureManager,
        std::shared_ptr<EventBus> eventBus,
        float windowScale,
        sf::Font* font) {
    MenuWithSelectorComponent partyMenuComponent;

    std::string partyMenuAssetPath = AssetPath::getUIComponentAssetPath(UIComponentType::PARTY_MENU);
    textureManager.loadTexture(partyMenuAssetPath);
    partyMenuComponent.initialize(
            eventBus,
            font,
            windowScale,
            textureManager.getTexture(partyMenuAssetPath),
            textureManager.getTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR)),
            ScreenPosition::TOP_LEFT);

    initializeMenuOptionComponent(0, "Charlie", UIComponentType::NO_COMPONENT_TYPE, partyMenuComponent);
    initializeMenuOptionComponent(1, "Louie", UIComponentType::NO_COMPONENT_TYPE, partyMenuComponent);
    initializeMenuOptionComponent(2, "Henry", UIComponentType::NO_COMPONENT_TYPE, partyMenuComponent);
    initializeMenuOptionComponent(3, "Edgar", UIComponentType::NO_COMPONENT_TYPE, partyMenuComponent);
    initializeMenuOptionComponent(4, "Victoria", UIComponentType::NO_COMPONENT_TYPE, partyMenuComponent);
    initializeMenuOptionComponent(5, "Tracy", UIComponentType::NO_COMPONENT_TYPE, partyMenuComponent);

    return partyMenuComponent;
}

MenuWithSelectorComponent UIComponentInitializer::initializeBattleMenuComponent(
        TextureManager& textureManager,
        std::shared_ptr<EventBus> eventBus,
        float windowScale,
        sf::Font* font,
        bool isPartyLeader,
        int indexOfCharacterInParty) {
    MenuWithSelectorComponent battleMenuComponent;
    ScreenPosition screenPosition = ScreenPosition::BOTTOM_LEFT;

    switch(indexOfCharacterInParty) {
        case 0:
            screenPosition = ScreenPosition::BOTTOM_LEFT;
            break;
        case 1:
            screenPosition = ScreenPosition::BOTTOM_SECOND_QUADRANT;
            break;
        case 2:
            screenPosition = ScreenPosition::BOTTOM_THIRD_QUADRANT;
            break;
        case 3:
            screenPosition = ScreenPosition::BOTTOM_RIGHT;
            break;
    }

    std::string battleMenuAssetPath = AssetPath::getUIComponentAssetPath(UIComponentType::BATTLE_CHARACTER_CHOICES_MENU);
    textureManager.loadTexture(battleMenuAssetPath);
    battleMenuComponent.initialize(
            eventBus,
            font,
            windowScale,
            textureManager.getTexture(battleMenuAssetPath),
            textureManager.getTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR)),
            screenPosition);

    initializeMenuOptionComponent(0, "ATTACK", UIComponentType::NO_COMPONENT_TYPE, battleMenuComponent);
    initializeMenuOptionComponent(1, "MAGIC", UIComponentType::NO_COMPONENT_TYPE, battleMenuComponent);
    initializeMenuOptionComponent(2, "ITEM", UIComponentType::NO_COMPONENT_TYPE, battleMenuComponent);

    if(isPartyLeader) {
        initializeMenuOptionComponent(3, "RUN", UIComponentType::NO_COMPONENT_TYPE, battleMenuComponent);
    }

    return battleMenuComponent;
}

void UIComponentInitializer::initializeMenuOptionComponent(
        int index,
        std::string displayText,
        UIComponentType opensToMenu,
        MenuWithSelectorComponent& startMenuComponent) {
    MenuOptionComponent menuOption;
    menuOption.initialize(index, displayText, opensToMenu);
    startMenuComponent.addMenuOption(menuOption);
}

void UIComponentInitializer::release(TextureManager &textureManager) {
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::DIALOGUE_MENU));
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::START_MENU));
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::PARTY_MENU));
}
