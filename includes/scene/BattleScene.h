#ifndef NEWNEW_BATTLESCENE_H
#define NEWNEW_BATTLESCENE_H


#include "Scene.h"
#include "../npc/NpcManager.h"
#include "../collisions/CollisionManager.h"
#include "ViewManager.h"
#include "battle/BattleState.h"
#include "../ui/manager/BattleUIManager.h"
#include "../events/event/ChangeSceneToPreviousSceneEvent.h"

class BattleScene : public Scene {

public:
    virtual void initialize(
            std::shared_ptr<EventBus> eventBus,
            std::string sceneName,
            std::string previousSceneName,
            TextureManager& textureManager,
            sf::Font* font,
            sf::Vector2u windowSize,
            sf::Vector2f defaultWindowSize) override;
    virtual void update(
            sf::Time elapsedTime,
            sf::RenderTexture& renderTexture,
            sf::View& view) override;
    virtual void draw(
            sf::RenderTarget& target,
            sf::RenderStates states) const override;
    virtual void release(TextureManager& textureManager) override;
    void handleControllerActionButtonPressed() override;
    void handleControllerMenuMoveButtonPressed(MoveDirection direction) override;

private:
    void changeToShowBattleChoicesState();
    void handleBattleChoiceChosen();
    void checkEnemyAppearedDialogueFinished();
    void checkRunningAwayDialogueFinished();

    BattleState state;
    BattleUIManager uiManager;
};


#endif //NEWNEW_BATTLESCENE_H
