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

    uiManager.openDialogue(BattleSceneDialogueEventName::ENEMY_APPEARED);
}

void BattleScene::update(
        sf::Time elapsedTime,
        bool isPaused,
        sf::RenderTexture& renderTexture,
        sf::View& view) {
    switch(state) {
        case BattleState::ENEMY_APPEARED_STATE:
        case BattleState::SHOW_BATTLE_CHOICES_STATE:
        case BattleState::RUN_AWAY_STATE:
            break;
    }

    uiManager.update(renderTexture, view, elapsedTime);
}

void BattleScene::draw(
        sf::RenderTarget& target,
        sf::RenderStates states) const {
//    states.transform *= getTransform();
//    states.texture = texture;
    target.clear(sf::Color::White);
    uiManager.drawToRenderTexture(static_cast<sf::RenderTexture&>(target));
}

void BattleScene::handleControllerActionButtonPressed() {
    switch(state) {
        case BattleState::ENEMY_APPEARED_STATE:
            changeToShowBattleChoicesState();
            break;
        case BattleState::SHOW_BATTLE_CHOICES_STATE:
            handleBattleChoiceChosen();
            break;
        case BattleState::RUN_AWAY_STATE:
            //TODO: I don't want to publish this until all the text is shown and has been clicked through. DialogueManager shouldn't close dialogue until its told to?
//            eventBus->publish(new ChangeSceneToPreviousSceneEvent());
            break;
    }
}

void BattleScene::handleControllerMenuMoveButtonPressed(MoveDirection direction) {
    uiManager.handleControllerMenuMoveButtonPressed(direction);
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
}

void BattleScene::release(TextureManager& textureManager) {
    uiManager.release(textureManager);
}