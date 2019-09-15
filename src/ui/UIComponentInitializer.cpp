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

    initializeStartMenuComponentOption(0, "Party", "", startMenuComponent);
    initializeStartMenuComponentOption(1, "Items", "", startMenuComponent);
    initializeStartMenuComponentOption(2, "Skills", "", startMenuComponent);
    initializeStartMenuComponentOption(3, "Options", "", startMenuComponent);
    initializeStartMenuComponentOption(4, "Save", "", startMenuComponent);
    initializeStartMenuComponentOption(5, "Exit", "", startMenuComponent);

    return startMenuComponent;
}

void UIComponentInitializer::initializeStartMenuComponentOption(int index, std::string displayText, std::string opensToMenu, MenuComponent& startMenuComponent) {
    MenuOptionComponent menuOption;
    menuOption.initialize(std::to_string(index), ObjectType::MENU_OPTION, index, displayText, opensToMenu);
    startMenuComponent.addMenuOption(menuOption);
}

void UIComponentInitializer::release(TextureManager &textureManager) {
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::DIALOGUE_BOX));
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::START_MENU));
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR));
}
