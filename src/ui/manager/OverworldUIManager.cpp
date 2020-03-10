#include "../../../includes/ui/manager/OverworldUIManager.h"

void OverworldUIManager::initializeComponents(
        TextureManager &textureManager,
        float windowScale,
        sf::Font *font,
        std::string sceneName) {
    textureManager.loadTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR));

    dialogueMenuComponent = uiComponentInitializer.initializeDialogueMenuComponent(textureManager, windowScale, font);
    startMenuComponent = uiComponentInitializer.initializeStartMenuComponent(textureManager, windowScale, font);
    partyMenuComponent = uiComponentInitializer.initializePartyMenuComponent(textureManager, windowScale, font);

    std::vector<DialogueEvent> entityDialogueEvents = xmlManager.loadEntityDialogueForScene(sceneName);
    dialogueMenuComponent.setEntityDialogueEvents(entityDialogueEvents);
}

void OverworldUIManager::openDialogue(std::string dialogueTextAssetName) {
    activeMenuComponent = &dialogueMenuComponent;
    activeMenuComponent->openDialogue(dialogueTextAssetName);
}

void OverworldUIManager::openMenu(UIComponentType menuTypeToOpen) {
    switch (menuTypeToOpen) {
        case PARTY_MENU:
            activeMenuComponent = &partyMenuComponent;
            break;
        case START_MENU:
            activeMenuComponent = &startMenuComponent;
            break;
        case BATTLE_CHARACTER_CHOICES_MENU:
            break;
        default:
            break;
    }
}

void OverworldUIManager::handleControllerActionButtonPressed() {
    if (activeMenuComponent != nullptr) {
        activeMenuComponent->handleControllerActionButtonPressed();
    }
}

std::string OverworldUIManager::handleControllerActionButtonPressedForStartMenu() {
    if (activeMenuComponent == &startMenuComponent) {
        return startMenuComponent.getActiveMenuOptionName();
    }

    return "";
}

//std::string BattleUIManager::handleControllerActionButtonPressedForBattleChoice() {
//    if (activeMenuComponent == &battleMenuComponent) {
//        std::string selectedOptionName = battleMenuComponent.getActiveMenuOptionName();
//
//        if(selectedOptionName == BattleSceneMenuChoice::ATTACK) {
//            printf("attack selected\n");
//        } else if(selectedOptionName == BattleSceneMenuChoice::MAGIC) {
//            printf("magic selected\n");
//        } else if(selectedOptionName == BattleSceneMenuChoice::ITEM) {
//            printf("item selected\n");
//        } else if(selectedOptionName == BattleSceneMenuChoice::RUN) {
//            printf("run selected\n");
//        } else {
//            printf("ERROR: something went wrong here\n");
//        }
//
//        return selectedOptionName;
//    }
//
//    return "";
//}

void OverworldUIManager::handleControllerMenuMoveButtonPressed(MoveDirection direction) {
    if (activeMenuComponent != nullptr) {
        activeMenuComponent->handleControllerMenuMoveButtonPressed(direction);
    }
}

void OverworldUIManager::release(TextureManager &textureManager) {
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR));
    UIManager::release(textureManager);
}
