#include "../../includes/ui/UIComponentInitializer.h"

DialogueMenuComponent UIComponentInitializer::initializeDialogueMenuComponent(TextureManager& textureManager, std::shared_ptr<EventBus> eventBus, float windowScale, sf::Font* font) {
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

MenuWithSelectorComponent UIComponentInitializer::initializeStartMenuComponent(TextureManager& textureManager, std::shared_ptr<EventBus> eventBus, float windowScale, sf::Font* font) {
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

MenuWithSelectorComponent UIComponentInitializer::initializePartyMenuComponent(TextureManager& textureManager, std::shared_ptr<EventBus> eventBus, float windowScale, sf::Font* font) {
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

MenuWithSelectorComponent UIComponentInitializer::initializeBattleMenuComponent(TextureManager& textureManager, std::shared_ptr<EventBus> eventBus, float windowScale, sf::Font* font) {
//    MenuWithSelectorComponent battleMenuComponent;
//
//    std::string partyMenuAssetPath = AssetPath::getUIComponentAssetPath(UIComponentType::PARTY_MENU);
//    textureManager.loadTexture(partyMenuAssetPath);
//    partyMenuComponent.initialize(
//            eventBus,
//            font,
//            windowScale,
//            textureManager.getTexture(partyMenuAssetPath),
//            textureManager.getTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR)),
//            ScreenPosition::TOP_LEFT);
//
//    initializeMenuOptionComponent(0, "Charlie", UIComponentType::NO_COMPONENT_TYPE, partyMenuComponent);
//    initializeMenuOptionComponent(1, "Louie", UIComponentType::NO_COMPONENT_TYPE, partyMenuComponent);
//    initializeMenuOptionComponent(2, "Henry", UIComponentType::NO_COMPONENT_TYPE, partyMenuComponent);
//    initializeMenuOptionComponent(3, "Edgar", UIComponentType::NO_COMPONENT_TYPE, partyMenuComponent);
//    initializeMenuOptionComponent(4, "Victoria", UIComponentType::NO_COMPONENT_TYPE, partyMenuComponent);
//    initializeMenuOptionComponent(5, "Tracy", UIComponentType::NO_COMPONENT_TYPE, partyMenuComponent);
//
//    return partyMenuComponent;
}

void UIComponentInitializer::initializeMenuOptionComponent(int index, std::string displayText, UIComponentType opensToMenu, MenuWithSelectorComponent& startMenuComponent) {
    MenuOptionComponent menuOption;
    menuOption.initialize(index, displayText, opensToMenu);
    startMenuComponent.addMenuOption(menuOption);
}

void UIComponentInitializer::release(TextureManager &textureManager) {
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::DIALOGUE_MENU));
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::START_MENU));
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::PARTY_MENU));
}
