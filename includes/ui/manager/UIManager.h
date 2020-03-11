#ifndef NEWNEW_UIMANAGER_H
#define NEWNEW_UIMANAGER_H


#include <SFML/Graphics/RenderTexture.hpp>
#include "../../asset/TextureManager.h"
#include "../../asset/AssetPath.h"
#include "../dialogue/DialogueManager.h"
#include "../UIComponentInitializer.h"
#include "../../util/XmlManager.h"

class UIManager {

public:
    void initialize(
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
    void closeCurrentMenuOrDialogue();
    bool checkActiveComponentActionFinished();
    UIComponentType getActiveMenuComponentType();

    virtual void handleControllerMenuButtonPressed() {};
    virtual void handleControllerActionButtonPressed() {};
    virtual void handleControllerCancelButtonPressed() {};
    virtual void handleControllerMenuMoveButtonPressed(MoveDirection direction) {};
    virtual void openDialogueWithSubstitutions(
            std::string dialogueTextAssetName,
            std::vector<std::string> textSubstitutions) {};
    virtual void openDialogue(std::string dialogueTextAssetName) {};
    virtual void openMenu(UIComponentType menuTypeToOpen) {};

    virtual std::string getMenuOptionSelectedOnControllerActionButtonPressed();
    virtual void release(TextureManager& textureManager);

protected:
    BaseMenuComponent* activeMenuComponent = nullptr;
    UIComponentInitializer uiComponentInitializer;
    XmlManager xmlManager;

    virtual void initializeComponents(
            TextureManager& textureManager,
            float windowScale,
            sf::Font* font,
            std::string sceneName) {};
    bool isAnyMenuOpen();
};


#endif //NEWNEW_UIMANAGER_H
