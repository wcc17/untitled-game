#ifndef NEWNEW_PLAYERENTITY_H
#define NEWNEW_PLAYERENTITY_H


#include "../../events/EventBus.h"
#include "../../events/event/ControllerMoveEvent.h"
#include "../../events/event/PlayerVicinityCollisionEvent.h"
#include "../../events/event/CloseDialogueEvent.h"
#include "../../events/event/ControllerActionEvent.h"
#include "../../events/event/OpenDialogueEvent.h"
#include "../../events/event/PlayerCollisionEvent.h"
#include "../../events/event/PlayerDoorCollisionEvent.h"
#include "../../events/event/PlayerPositionChangeEvent.h"
#include "../../events/event/ChangeSceneToNewMapEvent.h"
#include "../../events/event/ChangeSceneToBattleEvent.h"
#include "../components/EntityAnimation.h"
#include "../components/EntityCollidable.h"
#include "../components/EntityState.h"
#include "../components/EntityMovement.h"
#include "../../events/event/PlayerAndNpcCollisionEvent.h"

class PlayerEntity : public sf::Sprite {

public:
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture);
    void initializeForScene(const Collidable& collidable, const sf::Vector2u& mapTileSize);
    void update(sf::Time deltaTime);
    EntityCollidable getEntityCollidable() const;
    MoveDirection getLastFacingDirection() const;
    void release();
private:
    EntityState state;
    EntityAnimation entityAnimation;
    EntityCollidable entityCollidable;
    EntityMovement entityMovement;
    std::shared_ptr<EventBus> eventBus;
    MoveDirection currentDirection;
    sf::Vector2u mapTileSize;
    static Logger logger;

    void initializeAnimations();
    void handleStandingState(sf::Time deltaTime);
    void handleMovingState(sf::Time deltaTime);
    void handleInteractingState();
    void handleDoneInteractingState();
    void handleState(sf::Time deltaTime);
    void resetAfterFrame();
    void roundPosition();

    void handleActionButtonPressed();
    void adjustPlayerAndViewPositions();

    void onControllerMoveEvent(ControllerMoveEvent* event);
    void onControllerActionEvent(ControllerActionEvent* event);
    void onVicinityCollisionEvent(PlayerVicinityCollisionEvent* event);
    void onCloseDialogueEvent(CloseDialogueEvent* event);
    void onCollisionEvent(PlayerCollisionEvent* event);
    void onDoorCollisionEvent(PlayerDoorCollisionEvent* event);
    void onPlayerAndNpcCollisionEvent(PlayerAndNpcCollisionEvent* event);
};


#endif //NEWNEW_PLAYERENTITY_H
