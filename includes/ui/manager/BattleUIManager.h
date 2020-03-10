#ifndef NEWNEW_BATTLEUIMANAGER_H
#define NEWNEW_BATTLEUIMANAGER_H

#include "UIManager.h"
#include "../component/menu_component/DialogueMenuComponent.h"
#include "../component/menu_component/BattleChoiceMenuWithSelectorComponent.h"

class BattleUIManager : public UIManager {

public:
    std::string handleControllerActionButtonPressedForBattleChoice();
    void handleControllerCancelButtonPressed() override;
    void handleControllerMenuMoveButtonPressed(MoveDirection direction) override;
    void handleControllerActionButtonPressed() override;
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
    BattleChoiceMenuWithSelectorComponent battleMenuComponent;
    DialogueMenuComponent dialogueMenuComponent;
};


#endif //NEWNEW_BATTLEUIMANAGER_H
