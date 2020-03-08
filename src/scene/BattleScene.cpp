#include "../../includes/scene/BattleScene.h"
#include "../../includes/scene/battle/BattleSceneDialogueEventName.h"

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
            //TODO: where we actually choose an option I think
            break;
    }
}

void BattleScene::changeToShowBattleChoicesState() {
    uiManager.closeCurrentMenuOrDialogue();
    state = BattleState::SHOW_BATTLE_CHOICES_STATE;
    uiManager.openMenu(UIComponentType::BATTLE_CHARACTER_CHOICES_MENU);
}


void BattleScene::release(TextureManager& textureManager) {
    Scene::release(textureManager);
}

/**

(Top of screen) <nothing>
(Bottom of screen) An enemy has attacked!       BattleSceneDialogueEventName::ENEMY_APPEARED = "enemy_appeared"


(Top of screen)     What will you do?           BattleSceneDialogueEventName::ENEMY_APPEARED = "enemy_appeared"
(Bottom of screen)  Show action choice (Attack, Magic, Item) for each character in the party. Also show "Run" for the first character in the party  //TODO: who handles what text shows here?
                        Make user choose one of the above three options for each character in the party


IF RUN is chosen
    If run was successful
        (Top of screen) <nothing>
        (Bottom of screen) The party ran away! BattleSceneDialogueEventName::PARTY_RAN_AWAY = "party_ran_away"

    If run was unsuccessful
        (Top of screen) <nothing>
        (Bottom of screen) The party couldn't get away! BattleSceneDialogueEventName::PARTY_COULD_NOT_RUN = "party_could_not_run"

*/
