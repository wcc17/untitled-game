#ifndef NEWNEW_PLAYER_H
#define NEWNEW_PLAYER_H


#include "../../events/EventBus.h"
#include "../../events/event/ControllerMoveEvent.h"
#include "../../events/event/PlayerVicinityCollisionEvent.h"
#include "../../events/event/CloseDialogueEvent.h"
#include "../../events/event/ControllerActionEvent.h"
#include "../../events/event/OpenDialogueEvent.h"
#include "../../events/event/PlayerCollisionEvent.h"
#include "../../events/event/PlayerPositionChangeEvent.h"
#include "../character/EntityAnimation.h"
#include "../character/MovableEntity.h"
#include "../character/EntityCollidable.h"

class Player : public MovableEntity {

public:
    void initialize(std::shared_ptr<EventBus> eventBus, sf::Texture* texture, const Collidable& collidable);
    void update(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    EntityCollidable getEntityCollidable();
private:
    EntityState state;
    EntityAnimation entityAnimation;
    EntityCollidable entityCollidable;
    std::shared_ptr<EventBus> eventBus;
    bool actionButtonPressed = false;

    void initializeAnimations();
    void handleStandingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void handleMovingState(sf::Time deltaTime, const sf::Vector2u& mapTileSize);
    void handleInteractingState();
    void resetAfterFrame();
    void roundPosition();

    void handleActionButtonPressed();
    void adjustPlayerAndViewPositions();

    void onControllerMoveEvent(ControllerMoveEvent* event);
    void onControllerActionEvent(ControllerActionEvent* event);
    void onVicinityCollisionEvent(PlayerVicinityCollisionEvent* event);
    void onCloseDialogueEvent(CloseDialogueEvent* event);
    void onCollisionEvent(PlayerCollisionEvent* event);
};


#endif //NEWNEW_PLAYER_H
