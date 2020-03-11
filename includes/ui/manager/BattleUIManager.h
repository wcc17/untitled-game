#ifndef NEWNEW_BATTLEUIMANAGER_H
#define NEWNEW_BATTLEUIMANAGER_H

#include "UIManager.h"

class BattleUIManager : public UIManager {

public:
    void handleControllerMenuMoveButtonPressed(MoveDirection direction) override;
    void handleControllerActionButtonPressed() override;
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
    MenuWithSelectorComponent battleMenuComponent;
    DialogueMenuComponent dialogueMenuComponent;
};


#endif //NEWNEW_BATTLEUIMANAGER_H
