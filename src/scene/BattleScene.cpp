#include "../../includes/scene/BattleScene.h"
#include "../../includes/scene/battle/BattleSceneDialogueEventName.h"
#include "../../includes/scene/battle/BattleSceneMenuChoice.h"

void BattleScene::initialize(
        std::shared_ptr<EventBus> eventBus,
        std::string sceneName,
        std::string previousSceneName,
        TextureManager& textureManager,
        sf::Font* font,
        sf::Vector2u windowSize,
        sf::Vector2f defaultWindowSize) {

    Scene::initialize(eventBus, sceneName, previousSceneName, textureManager, font, windowSize, defaultWindowSize);
    uiManager.initialize(eventBus, textureManager, font, windowSize, defaultWindowSize, sceneName);

    state = BattleState::ENEMY_APPEARED_STATE;
    uiManager.openDialogue(BattleSceneDialogueEventName::ENEMY_APPEARED);
}

void BattleScene::update(
        sf::Time elapsedTime,
        sf::RenderTexture& renderTexture,
        sf::View& view) {
    switch(state) {
        case BattleState::ENEMY_APPEARED_STATE:
            checkEnemyAppearedDialogueFinished();
            break;
        case BattleState::SHOW_BATTLE_CHOICES_STATE:
            break;
        case BattleState::RUN_AWAY_STATE:
            checkRunningAwayDialogueFinished();
            break;
        case BattleState::BATTLE_OVER:
            break;
    }

    uiManager.update(renderTexture, view, elapsedTime);
}

void BattleScene::handleControllerActionButtonPressed() {
    switch(state) {
        case BattleState::ENEMY_APPEARED_STATE:
            uiManager.handleControllerActionButtonPressed();
            break;
        case BattleState::SHOW_BATTLE_CHOICES_STATE:
            handleBattleChoiceChosen();
            break;
        case BattleState::RUN_AWAY_STATE:
            uiManager.handleControllerActionButtonPressed();
            break;
        case BattleState::BATTLE_OVER:
            break;
    }
}

void BattleScene::draw(
        sf::RenderTarget& target,
        sf::RenderStates states) const {
//    states.transform *= getTransform();
//    states.texture = texture;
    target.clear(sf::Color::White);
    uiManager.drawToRenderTexture(static_cast<sf::RenderTexture&>(target));
}

void BattleScene::checkEnemyAppearedDialogueFinished() {
    if(uiManager.checkActiveComponentActionFinished()) {
        changeToShowBattleChoicesState();
    }
}

void BattleScene::checkRunningAwayDialogueFinished() {
    if(uiManager.checkActiveComponentActionFinished()) {
        uiManager.closeCurrentMenuOrDialogue();
        eventBus->publish(new ChangeSceneToPreviousSceneEvent());
        eventBus->publish(new CloseDialogueEvent());
        state = BattleState::BATTLE_OVER;
    }
}

void BattleScene::changeToShowBattleChoicesState() {
    uiManager.closeCurrentMenuOrDialogue();
    state = BattleState::SHOW_BATTLE_CHOICES_STATE;
    uiManager.openMenu(UIComponentType::BATTLE_CHARACTER_CHOICES_MENU);
}

void BattleScene::handleBattleChoiceChosen() {
    std::string battleChoiceSelected = uiManager.handleControllerActionButtonPressedForBattleChoice();

    if(battleChoiceSelected == BattleSceneMenuChoice::RUN) {
        state = BattleState::RUN_AWAY_STATE;
        uiManager.closeCurrentMenuOrDialogue();
        uiManager.openDialogue(BattleSceneDialogueEventName::PARTY_RAN_AWAY);
    }
    //TODO: handle other choices
}

void BattleScene::handleControllerMenuMoveButtonPressed(MoveDirection direction) {
    uiManager.handleControllerMenuMoveButtonPressed(direction);
}

void BattleScene::release(TextureManager& textureManager) {
    uiManager.release(textureManager);
}