#ifndef NEWNEW_OVERWORLDUIMANAGER_H
#define NEWNEW_OVERWORLDUIMANAGER_H


#include "UIManager.h"
#include "../component/menu_component/DialogueMenuComponent.h"
#include "../component/menu_component/StartMenuWithSelectorComponent.h"
#include "../component/menu_component/PartyMenuWithSelectorComponent.h"

class OverworldUIManager : public UIManager {

public:
    void handleControllerActionButtonPressed() override;
    void handleControllerMenuMoveButtonPressed(MoveDirection direction) override;
    void openDialogue(std::string dialogueTextAssetName) override;
    void openMenu(UIComponentType menuTypeToOpen) override;
    void release(TextureManager& textureManager) override;

    std::string handleControllerActionButtonPressedForStartMenu();

protected:
    void initializeComponents(
            TextureManager &textureManager,
            float windowScale,
            sf::Font *font,
            std::string sceneName) override;

private:
    StartMenuWithSelectorComponent startMenuComponent;
    DialogueMenuComponent dialogueMenuComponent;
    PartyMenuWithSelectorComponent partyMenuComponent;
};


#endif //NEWNEW_OVERWORLDUIMANAGER_H
