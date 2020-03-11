#ifndef NEWNEW_OVERWORLDUIMANAGER_H
#define NEWNEW_OVERWORLDUIMANAGER_H


#include "UIManager.h"

class OverworldUIManager : public UIManager {

public:
    void handleControllerActionButtonPressed() override;
    void handleControllerMenuMoveButtonPressed(MoveDirection direction) override;
    void openDialogueWithSubstitutions(
            std::string dialogueTextAssetName,
            std::vector<std::string> textSubstitutions) override;
    void openDialogue(std::string dialogueTextAssetName) override;
    void openMenu(UIComponentType menuTypeToOpen) override;
    void release(TextureManager& textureManager) override;

protected:
    void initializeComponents(
            TextureManager &textureManager,
            float windowScale,
            sf::Font *font,
            std::string sceneName) override;

private:
    MenuWithSelectorComponent startMenuComponent;
    DialogueMenuComponent dialogueMenuComponent;
    MenuWithSelectorComponent partyMenuComponent;
};


#endif //NEWNEW_OVERWORLDUIMANAGER_H
