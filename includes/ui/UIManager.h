#ifndef NEWNEW_UIMANAGER_H
#define NEWNEW_UIMANAGER_H


#include <SFML/Graphics/RenderTexture.hpp>
#include "../asset/TextureManager.h"
#include "../asset/AssetPath.h"
#include "dialogue/DialogueManager.h"
#include "component/menu_component/MenuWithSelectorComponent.h"
#include "component/menu_component/DialogueMenuComponent.h"
#include "UIComponentInitializer.h"
#include "../util/XmlManager.h"

class UIManager {

public:
    void initialize(
            std::shared_ptr<EventBus> eventBus,
            TextureManager& textureManager,
            sf::Font* font,
            sf::Vector2u windowSize,
            sf::Vector2f defaultWindowSize,
            std::string sceneName);
    void update(
            sf::RenderTexture& renderTexture,
            sf::View& view,
            sf::Time deltaTime);
    void drawToRenderTexture(sf::RenderTexture& renderTexture) const;
    void release(TextureManager& textureManager);

    void handleControllerMenuButtonPressed();
    void handleControllerActionButtonPressed();
    void handleControllerCancelButtonPressed();
    void handleControllerMenuMoveButtonPressed(MoveDirection direction);
    void openDialogue(std::string dialogueTextAssetName);
    void openMenu(UIComponentType menuTypeToOpen);
    void closeCurrentMenuOrDialogue();

private:
    std::shared_ptr<EventBus> eventBus;
    XmlManager xmlManager;

    UIComponentInitializer uiComponentInitializer;
    BaseMenuComponent* activeMenuComponent = nullptr;

    MenuWithSelectorComponent startMenuComponent;
    DialogueMenuComponent dialogueMenuComponent;
    MenuWithSelectorComponent partyMenuComponent;
    MenuWithSelectorComponent battleChoiceMenuComponent;

    void initializeComponents(
            TextureManager& textureManager,
            float windowScale,
            sf::Font* font,
            std::string sceneName);
};


#endif //NEWNEW_UIMANAGER_H
