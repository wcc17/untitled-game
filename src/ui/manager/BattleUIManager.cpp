#include "../../../includes/ui/manager/BattleUIManager.h"
#include "../../../includes/scene/battle/BattleSceneMenuChoice.h"

void BattleUIManager::initializeComponents(
        TextureManager &textureManager,
        float windowScale,
        sf::Font *font,
        std::string sceneName) {
    textureManager.loadTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR)); //TODO: probably should just be in UIManager

    dialogueMenuComponent = uiComponentInitializer.initializeDialogueMenuComponent(textureManager, windowScale, font);
    //TODO: I need four of these and they're specific to battle menu. Need to be able to initialize these components outside of here or at least conditionally depending on what scene we're in.
    battleMenuComponent = uiComponentInitializer.initializeBattleMenuComponent(textureManager, windowScale, font, true, 0);

    std::vector<DialogueEvent> entityDialogueEvents = xmlManager.loadEntityDialogueForScene(sceneName); //TODO: need to see how this works for the battle scene
    dialogueMenuComponent.setEntityDialogueEvents(entityDialogueEvents);
}

void BattleUIManager::openDialogue(std::string dialogueTextAssetName) {
    activeMenuComponent = &dialogueMenuComponent;
    activeMenuComponent->openDialogue(dialogueTextAssetName);
}

void BattleUIManager::openMenu(UIComponentType menuTypeToOpen) {
    switch (menuTypeToOpen) {
        case PARTY_MENU:
            break;
        case START_MENU:
            break;
        case BATTLE_CHARACTER_CHOICES_MENU:
            activeMenuComponent = &battleMenuComponent;
            break;
        default:
            break;
    }
}

std::string BattleUIManager::handleControllerActionButtonPressedForBattleChoice() {
    if (activeMenuComponent == &battleMenuComponent) {
        std::string selectedOptionName = battleMenuComponent.getActiveMenuOptionName();

        if(selectedOptionName == BattleSceneMenuChoice::ATTACK) {
            printf("attack selected\n");
        } else if(selectedOptionName == BattleSceneMenuChoice::MAGIC) {
            printf("magic selected\n");
        } else if(selectedOptionName == BattleSceneMenuChoice::ITEM) {
            printf("item selected\n");
        } else if(selectedOptionName == BattleSceneMenuChoice::RUN) {
            printf("run selected\n");
        } else {
            printf("ERROR: something went wrong here\n");
        }

        return selectedOptionName;
    }

    return "";
}

void BattleUIManager::handleControllerCancelButtonPressed() {
//    if (activeMenuComponent != nullptr) {
//        activeMenuComponent->handleControllerCancelButtonPressed(eventBus);
//    }

//    closeCurrentMenuOrDialogue();
//    eventBus->publish(new UnPauseGameEvent());
}

void BattleUIManager::handleControllerMenuMoveButtonPressed(MoveDirection direction) {
    if (activeMenuComponent != nullptr) {
        activeMenuComponent->handleControllerMenuMoveButtonPressed(direction);
    }
}

void BattleUIManager::release(TextureManager &textureManager) {
    textureManager.releaseTexture(AssetPath::getUIComponentAssetPath(UIComponentType::MENU_SELECTOR));
    UIManager::release(textureManager);
}
