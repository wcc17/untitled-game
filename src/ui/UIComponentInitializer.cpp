#include "../../includes/ui/UIComponentInitializer.h"

DialogueMenuComponent UIComponentInitializer::initializeDialogueMenuComponent(TextureManager& textureManager, float windowScale, sf::Font* font) {
    DialogueMenuComponent dialogueMenuComponent;

    std::string dialogueBoxAssetPath = AssetPath::getUIComponentAssetPath(UIComponentType::DIALOGUE_BOX);
    textureManager.loadTexture(dialogueBoxAssetPath);
    dialogueMenuComponent.initialize(
            font,
            windowScale,
            UIComponentType::DIALOGUE_BOX,
            ObjectType::MENU,
            textureManager.getTexture(dialogueBoxAssetPath),
            ScreenPosition::BOTTOM_LEFT,
            sf::Vector2f(0, 0));

    MenuOptionComponent textOptionComponent;
    std::string displayText = "";
    std::string opensToMenu = "";
    textOptionComponent.initialize(std::to_string(0), ObjectType::MENU_OPTION, 0, displayText, opensToMenu);
    dialogueMenuComponent.addMenuOption(textOptionComponent);

    return dialogueMenuComponent;
}

MenuComponent UIComponentInitializer::initializeStartMenuComponent(TextureManager& textureManager, float windowScale, sf::Font* font, sf::FloatRect selectorBounds) {
    MenuComponent startMenuComponent;

    std::string startMenuAssetPath = AssetPath::getUIComponentAssetPath(UIComponentType::START_MENU);
    textureManager.loadTexture(startMenuAssetPath);
    startMenuComponent.initialize(
            font,
            windowScale,
            UIComponentType::START_MENU,
            ObjectType::MENU,
            textureManager.getTexture(startMenuAssetPath),
            ScreenPosition::TOP_RIGHT,
            sf::Vector2f(selectorBounds.width, 0));

    initializeMenuOptionComponent(0, "Party", UIComponentType::PARTY_MENU, startMenuComponent);
    initializeMenuOptionComponent(1, "Items", "", startMenuComponent);
    initializeMenuOptionComponent(2, "Skills", "", startMenuComponent);
    initializeMenuOptionComponent(3, "Options", "", startMenuComponent);
    initializeMenuOptionComponent(4, "Save", "", startMenuComponent);
    initializeMenuOptionComponent(5, "Exit", "", startMenuComponent);

    return startMenuComponent;
}

MenuComponent UIComponentInitializer::initializePartyMenuComponent(TextureManager& textureManager, float windowScale, sf::Font* font, sf::FloatRect selectorBounds) {
    MenuComponent partyMenuComponent;

    std::string partyMenuAssetPath = AssetPath::getUIComponentAssetPath(UIComponentType::PARTY_MENU);
    textureManager.loadTexture(partyMenuAssetPath);
    partyMenuComponent.initialize(
            font,
            windowScale,
            UIComponentType::PARTY_MENU,
            ObjectType::MENU,
            textureManager.getTexture(partyMenuAssetPath),
            ScreenPosition::TOP_LEFT,
            sf::Vector2f(selectorBounds.width, 0));

    //TODO: need to eventually pass these in from somewhere? it doesn't matter yet so just manually initializing them here
    initializeMenuOptionComponent(0, "Charlie", "", partyMenuComponent);
    initializeMenuOptionComponent(1, "Louie", "", partyMenuComponent);
    initializeMenuOptionComponent(2, "Henry", "", partyMenuComponent);
    initializeMenuOptionComponent(3, "Edgar", "", partyMenuComponent);
    initializeMenuOptionComponent(4, "Victoria", "", partyMenuComponent);
    initializeMenuOptionComponent(5, "Tracy", "", partyMenuComponent);

    return partyMenuComponent;
}

void UIComponentInitializer::initializeMenuOptionComponent(int index, std::string displayText, std::string opensToMenu, MenuComponent& startMenuComponent) {
    MenuOptionComponent menuOption;
    menuOption.initialize(std::to_string(index), ObjectType::MENU_OPTION, index, displayText, opensToMenu);
    startMenuComponent.addMenuOption(menuOption);
}

void UIComponentInitializer::release(TextureManager &textureManager) {
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::DIALOGUE_BOX));
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::START_MENU));
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::PARTY_MENU));
}
